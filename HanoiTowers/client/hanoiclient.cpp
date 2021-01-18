/*
 * Copyright (C) 2018-2020 QuasarApp.
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
#include <useravatar.h>
#include <sqldb.h>
#include <sqldbwriter.h>
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

    } else if (H_16<QH::PKG::UserMember>() == pkg.hdr.command) {
        QH::PKG::UserMember obj(pkg);

        LocalUser user(&obj);
        auto action = [&obj](auto object) {
            auto localuser = object.template dynamicCast<LocalUser>();

            if (!localuser)
                return false;

            localuser->setToken(obj.token());
            localuser->setOnline(true);

            return true;
        };

        if (!db()->changeObjects(user, action)) {
            return QH::ParserResult::Error;
        };

        setStatus(Status::Logined);
    }

    return QH::ParserResult::NotProcessed;
}

QStringList HanoiClient::SQLSources() const {
    return {
        ":/sql/sql/database.sql"
    };
}

void HanoiClient::handleError(unsigned char status, const QString &error) {
    if (status == ErrorCodes::PermissionDenied) {
        setStatus(Status::Connected);
    }

    QmlNotificationService::NotificationService::getService()->setNotify(
                tr("Jnline error"), error, "",
                QmlNotificationService::NotificationData::Error);
}

bool HanoiClient::p_login(const QString& userId, const QByteArray &hashPassword) {
    QH::PKG::AuthRequest request;
    request.setId(userId);
    request.setRequest(QH::PKG::UserRequestType::Login);

    if (hashPassword.isEmpty()) {
        auto localUser = getLocalUser(userId);
        if (!(localUser && localUser->token().isValid())) {
            emit requestError("User '" + userId + "' have a invalid token.");
            return false;
        }

        request.setToken(localUser->token());
    }

    return sendData(&request, _serverAddress);
}

bool HanoiClient::p_signIn(const QString &userId, const QByteArray& hashPassword) {
    QH::PKG::AuthRequest request;
    request.setId(userId);
    request.setAuthenticationData(hashPassword);
    request.setRequest(QH::PKG::UserRequestType::SignIn);

    return sendData(&request, _serverAddress);
}

bool HanoiClient::userDatarequest(const QByteArray &userId) {
    UserDataRequest request;
    request.setId(userId);

    return sendData(&request, _serverAddress);
}

QSharedPointer<LocalUser> HanoiClient::getLocalUser(const QString &userId) const {
    LocalUser request;
    request.setId(userId);

    if (!db()) {
        return nullptr;
    }

    return db()->getObject(request);
}

Status HanoiClient::getStatus() const {
    return _status;
}

void HanoiClient::setStatus(const Status &status) {
    if (_status != status) {
        _status = status;
        emit statusChanged(static_cast<unsigned char>(_status));
    }
}

bool HanoiClient::setNewAvatar(const QString &userId, const QImage &image) {
    auto avatarData = QSharedPointer<UserAvatar>::create();
    avatarData->setId(userId);

    QByteArray array;
    QDataStream stram(&array, QIODevice::WriteOnly);

    stram << image;
    avatarData->setImage(array);

    if (!db()->updateObject(avatarData)) {
        return false;
    }

    auto profile = getLocalUser(userId);

    if (profile->online()) {
        return sendData(avatarData.data(), _serverAddress);
    }


    return true;
}

QImage HanoiClient::userAvatar(const QString &userId) const {
    UserAvatar avatarData;
    avatarData.setId(userId);

    auto result = db()->getObject(avatarData);

    if (result) {
        return QImage::fromData(result->image());
    }

    return {};
}

QString HanoiClient::currentUserId() const {
    return _currentUserId;
}

QSharedPointer<LocalUser> HanoiClient::currentProfile() const {
    return getLocalUser(_currentUserId);
}

QSharedPointer<LocalUser> HanoiClient::createLocalUser(const QString &login) {
    auto user = QSharedPointer<LocalUser>::create();
    user->setId(login);
    user->setUpdateTime(time(nullptr));

    return user;
}

bool HanoiClient::addProfile(const LocalUser& user) {

    auto localUser = QSharedPointer<LocalUser>::create();
    localUser->copyFrom(&user);
    localUser->setUpdateTime(time(nullptr));

    if (auto database = db()) {
        return database->insertObject(localUser);
    }

    return false;

}

bool HanoiClient::updateProfile(const LocalUser& user) {
    auto localUser = QSharedPointer<LocalUser>::create();
    localUser->copyFrom(&user);

    if (auto database = db()) {
        return database->updateObject(localUser);
    }

    return true;
}

bool HanoiClient::login(const QString &userId, const QString &rawPassword) {

    auto user = getLocalUser(userId);

    if (!user || !user->isValid()) {
        emit requestError("User '" + userId + "' is not exists");
        return false;
    }

    _currentUserId = userId;

    emit profileChanged(user);

    if (user->online() && !p_login(userId, hashgenerator(rawPassword.toLatin1()))) {
        return false;
    }

    return true;

}

bool HanoiClient::registerUser(const QString &userId, const QString &rawPassword) {
    auto user = getLocalUser(userId);

    if (user) {
        emit requestError("User '" + userId + "' is alredy exists");
        return false;
    }

    emit profileChanged(user);

    return p_signIn(userId, hashgenerator(rawPassword.toLatin1()));
}

bool HanoiClient::registerOflineUser(const QString &login, const QString& username) {
    auto user = createLocalUser(login);
    user->setName(username);

    if (!db()->insertObject(user)) {
        return false;
    }

    emit profileChanged(user);

    return true;
}

bool HanoiClient::removeUser(const QString &userId) {
    auto user = getLocalUser(userId);
    QH::PKG::AuthRequest request;
    request.setId(user->getId());
    request.setRequest(UserRequestType::Remove);

    return sendData(&request, _serverAddress);
}

void HanoiClient::connectToServer(const QH::HostAddress &host) {
    addNode(host);
    _serverAddress = host;
}

QList<UserPreview> HanoiClient::localUsersPreview() {
    LocalRecordsTable query;
    auto result = db()->getObject(query);

    if (!result)
        return {};

    return result->data();
}

void HanoiClient::nodeConfirmend(const QH::HostAddress &node) {
    setStatus(Status::Connected);
    DataBaseNode::nodeConfirmend(node);

}

void HanoiClient::nodeConnected(const QH::HostAddress &node) {
    DataBaseNode::nodeConnected(node);
}

void HanoiClient::nodeDisconnected(const QH::HostAddress &node) {
    setStatus(Status::Dissconnected);
    DataBaseNode::nodeDisconnected(node);
}

QByteArray HanoiClient::hashgenerator(const QByteArray &data) {
    if (data.isEmpty())
        return {};

    return DataBaseNode::hashgenerator(data);
}


