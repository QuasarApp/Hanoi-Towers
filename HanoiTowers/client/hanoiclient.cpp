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
#include "hanoierrorcodes.h"
#include "localrecordstable.h"

HanoiClient::HanoiClient() {

    initSqlDb("",
              new QH::SqlDB(),
              new QH::SqlDBWriter());
}

QH::ParserResult HanoiClient::parsePackage(const QH::Package &pkg,
                                           const QH::AbstractNodeInfo *sender) {
    auto parentResult = DataBaseNode::parsePackage(pkg, sender);
    if (parentResult != QH::ParserResult::NotProcessed) {
        return parentResult;
    }

    if (H_16<UserData>() == pkg.hdr.command) {
        auto obj = QSharedPointer<UserData>::create(pkg);

        if (!db()->updateObject(obj)) {
            return QH::ParserResult::Error;
        }

        emit profileIsUpdated();

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

void HanoiClient::handleError(QH::ErrorCodes::Code , const QString &error) {

    QmlNotificationService::NotificationService::getService()->setNotify(
                tr("Jnline error"), error, "",
                QmlNotificationService::NotificationData::Error);
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

bool HanoiClient::sendUserData(const QSharedPointer<LocalUser> &data) {
    UserData result(*data->userData());

    return sendData(&result, serverAddress());

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
            return sendUserData(obj);
        }

        return true;
    };

    if (!db()->changeObjects(profile, updateAction))  {
        return false;
    }

    return true;
}

bool HanoiClient::addProfile(const LocalUser& user) {

    if (!db())
        return false;

    auto localUser = QSharedPointer<LocalUser>::create();
    localUser->copyFrom(&user);
    localUser->setUpdateTime(time(nullptr));

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

    if ( user->online()) {
        connectToServer();
    }

    return true;
}

bool HanoiClient::updateProfile(const LocalUser& user) {
    auto localUser = QSharedPointer<LocalUser>::create();
    localUser->copyFrom(&user);

    if (auto database = db()) {
        return database->updateObject(localUser);
    }

    if (isOnlineAndLoginned(localUser)) {
        return sendUserData(localUser);
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


