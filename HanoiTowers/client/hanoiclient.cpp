/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiclient.h"
#include <qmlnotifyservice.h>
#include <usermember.h>
#include <userdata.h>
#include <sqldbcache.h>
#include <localuser.h>
#include <authrequest.h>
#include <userdatarequest.h>
#include <asyncsqldbwriter.h>
#include <sqldb.h>
#include <sqldbwriter.h>
#include <cacheddbobjectsrequest.h>
#include <getmaxintegerid.h>
#include <QBuffer>
#include <getsinglevalue.h>
#include <dataconverter.h>
#include <setsinglevalue.h>
#include <worldupdate.h>
#include <fixworldrequest.h>
#include <worldclient.h>
#include "hanoierrorcodes.h"
#include "localrecordstable.h"

HanoiClient::HanoiClient() {

    initSqlDb("",
              new QH::SqlDB(),
              new QH::SqlDBWriter());

    qRegisterMetaType<QSharedPointer<LocalUser>>();
    qRegisterMetaType<QSet<UserPreview>>();
    qRegisterMetaType<QSharedPointer<UserPreview>>();

    registerPackageType<UserData>();
    registerPackageType<FixWorldRequest>();
    registerPackageType<World>();
    registerPackageType<WorldUpdate>();

    _world = QSharedPointer<WorldClient>::create();

    connect(_world.data(), &WorldClient::sigBestUserChanged,
            this, &HanoiClient::handleNewBestUser,
            Qt::QueuedConnection);

    connect(this, &HanoiClient::currentUserChanged,
            this, &HanoiClient::handleCurrentUserChanged,
            Qt::QueuedConnection);
}

HanoiClient::~HanoiClient() {
}

QH::ParserResult HanoiClient::parsePackage(const QSharedPointer<QH::PKG::AbstractData> &pkg,
                                           const QH::Header &pkgHeader,
                                           const QH::AbstractNodeInfo *sender) {

    auto parentResult = SingleClient::parsePackage(pkg, pkgHeader, sender);
    if (parentResult != QH::ParserResult::NotProcessed) {
        return parentResult;
    }

    if (H_16<UserData>() == pkg->cmd()) {        
        if (!workWithUserData(pkg.staticCast<UserData>())) {
            return QH::ParserResult::Error;

        }
        return QH::ParserResult::Processed;

    }

    if (H_16<World>() == pkg->cmd()) {
        _world->copyFrom(pkg.data());

        emit worldInited(_world->getData());

        return QH::ParserResult::Processed;
    }

    if (H_16<WorldUpdate>() == pkg->cmd()) {
        if (!_world) {
            return QH::ParserResult::Error;
        }

        auto wUpdate = pkg.staticCast<WorldUpdate>();

        if (!_world->applyUpdate(*wUpdate)) {
            FixWorldRequest rquest;
            rquest.setWorldVersion(_world->getWorldVersion() + 1);

            if (!sendData(&rquest, sender->networkAddress())) {
                return QH::ParserResult::Error;
            }

            return QH::ParserResult::Processed;
        }

        emit worldChanged(wUpdate);

        return QH::ParserResult::Processed;
    }

    return QH::ParserResult::NotProcessed;
}

QStringList HanoiClient::SQLSources() const {
    return {
        ":/sql/sql/database.sql"
    };
}

QH::HostAddress HanoiClient::serverAddress() const {
    return QH::HostAddress{DEFAULT_HANOI_ADDRESS, DEFAULT_HANOI_PORT};
}

QSharedPointer<LocalUser> HanoiClient::getLocalUser(const QString &userId) const {
    LocalUser request;
    request.setId(userId);

    if (!db()) {
        return nullptr;
    }

    return db()->getObject(request);
}

bool HanoiClient::sendUserData(QSharedPointer<UserData> data) {
    data->setSignToken(getMember().getSignToken());
    return sendData(data.data(), serverAddress());
}

bool HanoiClient::isOnline(const QSharedPointer<LocalUser> &data) {
    if (!data->isOnline()) {
        return false;
    }

    return getStatus() >= QH::ClientStatus::Connected;
}

bool HanoiClient::isOnlineAndLoginned(const QSharedPointer<LocalUser> &data) {

    if (!isOnline(data)) {
        return false;
    }

    if (!data->token().isValid()) {
        return false;
    }

    return getStatus() >= QH::ClientStatus::Logined;

}

bool HanoiClient::workWithUserData(const QSharedPointer<UserData>& obj) {
    auto userId = getMember().getId();

    QSharedPointer<LocalUser> localUser;

    if (userId == obj->getId()) {
        localUser = getLocalUser(obj->getId().toString());

        if (obj->updateTime() > localUser->updateTime()) {
            localUser->setUserData(obj->userData());
            if (!db()->updateObject(obj)) {
                return false;
            }

            QmlNotificationService::NotificationService::getService()->setNotify(
                        tr("Local user has been updated"), tr("local user accept nbew data from the server."), "",
                        QmlNotificationService::NotificationData::Normal);

        }
    } else {
        localUser = QSharedPointer<LocalUser>::create();
        localUser->setUserData(obj->userData());
        _usersCache[obj->getId().toString()] = localUser;
    }

    emit userDataChanged(localUser);


    return true;
}

bool HanoiClient::setNewAvatar(const QString &userId, const QByteArray &image) {

    auto profile = LocalUser();
    profile.setUserId(userId);

    auto updateAction = [this, image](const QSharedPointer<QH::PKG::DBObject>& object) {

        auto obj = object.dynamicCast<LocalUser>();

        if (!obj) {
            return false;
        }

        obj->setAvatar(image);

        if (isOnlineAndLoginned(obj)) {
            return sendUserData(DataConverter::toUserDataPtr(obj));
        }

        return true;
    };

    if (!db()->changeObjects(profile, updateAction))  {
        return false;
    }

    return true;
}

bool HanoiClient::subscribeToWorld() {
    return subscribe(_world->subscribeId());
}

bool HanoiClient::getUserData(const QString& userId) {
    if (_usersCache.contains(userId)) {
        emit userDataChanged(_usersCache[userId]);
        return true;
    }

    UserDataRequest request;
    request.setId(userId);

    auto action = [this](const QSharedPointer<const QH::PKG::AbstractData> & resp) {
        auto obj = resp.dynamicCast<const UserData>();
        if (obj)
            subscribe(obj->subscribeId());
    };

    return restRequest(&request, action);
}

bool HanoiClient::addProfile(const LocalUser& user) {

    if (!db())
        return false;

    auto localUser = QSharedPointer<LocalUser>::create().
            staticCast<QH::PKG::DBObject>();
    localUser->copyFrom(&user);

    if (!db()->insertObject(localUser)) {
        return false;
    }

    return true;
}

bool HanoiClient::setProfile(const QString &userId,
                             QSharedPointer<LocalUser>* selectedProfileData) {
    auto user = getLocalUser(userId);

    if (!user || !user->isValid()) {
        emit requestError(0, "User '" + userId + "' is not exists");
        return false;
    }

    if (selectedProfileData) {
        *selectedProfileData = user;
    }

    emit userDataChanged(user);

    if ( user->online() && connectToServer()) {
        auto userMember = DataConverter::toUserMember(user);
        login(userMember);
    }

    return true;
}

bool HanoiClient::updateProfile(const LocalUser& user) {
    auto localUser = QSharedPointer<LocalUser>::create();
    localUser->copyFrom(&user);
    localUser->setUpdateTime(time(nullptr));

    if (auto database = db()) {
        if (!database->updateObject(localUser))
            return false;
    }

    if (isOnlineAndLoginned(localUser)) {
        return sendUserData(DataConverter::toUserDataPtr(localUser));
    }

    return true;
}

QList<UserPreview> HanoiClient::localUsersPreview() {
    LocalRecordsTable query;
    auto result = db()->getObject(query);

    if (!result)
        return {};

    return result->data();
}

void HanoiClient::handleNewBestUser(QString userId) {
    unsubscribe(QH::PKG::UserMember{_bestUserId}.subscribeId());
    _bestUserId = userId;

    UserDataRequest request;
    request.setId(userId);

    auto action = [this](const QSharedPointer<const QH::PKG::AbstractData> & resp) {
        auto obj = resp.dynamicCast<const UserData>();
        if (obj)
            subscribe(obj->subscribeId());
    };

    if (!restRequest(&request, action)) {
        QuasarAppUtils::Params::log("Fail to get information about best user.",
                                    QuasarAppUtils::Error);
    }
}

void HanoiClient::handleCurrentUserChanged() {
    auto member = getMember();
    if (auto user = getLocalUser(member.getId().toString())) {
        user->setToken(member.getSignToken());
        user->setOnline(true);

        if (auto database = db()) {

            using SetSingleVal = QSharedPointer<QH::PKG::SetSingleValue>;

            auto request = SetSingleVal::create(QH::DbAddress("Users", member.getId().toString()),
                                                "token", member.getSignToken().toBytes());

            if (database->updateObject(request)) {
                emit userDataChanged(user);
            } else {
                emit requestError(0, tr("Internal Error, server send invalid data,"
                                 " and this data can't be saved into local database."));
            }
        }
    }
}

