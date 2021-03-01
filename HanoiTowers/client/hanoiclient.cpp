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
#include <world.h>
#include <worldupdate.h>
#include <fixworldrequest.h>
#include "hanoierrorcodes.h"
#include "localrecordstable.h"

HanoiClient::HanoiClient() {

    initSqlDb("",
              new QH::SqlDB(),
              new QH::SqlDBWriter());

    qRegisterMetaType<QSharedPointer<LocalUser>>();

    registerPackageType<UserData>();
    registerPackageType<FixWorldRequest>();
    registerPackageType<World>();
    registerPackageType<WorldUpdate>();

    _world = QSharedPointer<World>::create();
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
        auto obj = pkg.staticCast<UserData>();
        auto localUser = getLocalUser(obj->name());

        if (obj->updateTime() > localUser->updateTime()) {
            localUser->setUserData(obj->userData());
            if (!db()->updateObject(obj)) {
                return QH::ParserResult::Error;
            }

            QmlNotificationService::NotificationService::getService()->setNotify(
                        tr("Local user has been updated"), tr("local user accept nbew data from the server."), "",
                        QmlNotificationService::NotificationData::Normal);

            emit profileChanged(localUser);
        }

        return QH::ParserResult::Processed;

    }

    if (H_16<World>() == pkg->cmd()) {
        _world = pkg.staticCast<World>();
        return QH::ParserResult::Processed;
    }

    if (H_16<WorldUpdate>() == pkg->cmd()) {
        if (!_world) {
            return QH::ParserResult::Error;
        }

        if (!_world->applyUpdate(*static_cast<WorldUpdate*>(pkg.data()))) {
            FixWorldRequest rquest;
            rquest.setWorldVersion(_world->getWorldVersion() + 1);

            if (!sendData(&rquest, sender->networkAddress())) {
                return QH::ParserResult::Error;
            }
        }
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

void HanoiClient::incomingData(AbstractData *pkg, const QH::AbstractNodeInfo *sender) {
    Q_UNUSED(sender);

    if (pkg->cmd() == H_16<UserMember>()) {
        if (auto user = getLocalUser(static_cast<UserMember*>(pkg)->getId().toString())) {
            user->setToken(static_cast<UserMember*>(pkg)->token());
            user->setOnline(true);

            if (auto database = db()) {

                using SetSingleVal = QSharedPointer<QH::PKG::SetSingleValue>;

                auto request = SetSingleVal::create(QH::DbAddress("Users", static_cast<UserMember*>(pkg)->getId().toString()),
                                                    "token", static_cast<UserMember*>(pkg)->token().toBytes());

                if (database->updateObject(request)) {
                    emit profileChanged(user);
                } else {
                    emit requestError(0, tr("Internal Error, server send invalid data,"
                                     " and this data can't be saved into local database."));
                }
            }
        }
    }
}


bool HanoiClient::userDatarequest(const QByteArray &userId) {
    UserDataRequest request;
    request.setId(userId);

    return sendData(&request, serverAddress());
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
    data->setToken(getMember().token());
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

    emit profileChanged(user);

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


