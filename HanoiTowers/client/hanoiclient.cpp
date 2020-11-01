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
#include "hanoierrorcodes.h"

HanoiClient::HanoiClient() {
    initSqlDb("", new QH::SqlDBCache(DEFAULT_UPDATE_INTERVAL, QH::SqlDBCasheWriteMode::Force));

}

QH::ParserResult HanoiClient::parsePackage(const QH::Package &pkg,
                                           const QH::AbstractNodeInfo *sender) {
    auto parentResult = DataBaseNode::parsePackage(pkg, sender);
    if (parentResult != QH::ParserResult::NotProcessed) {
        return parentResult;
    }

    if (H_16<UserData>() == pkg.hdr.command) {
        UserData obj(pkg);

        QH::BaseId requesterId = getSender(sender, &obj);

        if (setObject(requesterId, &obj) != QH::DBOperationResult::Allowed) {
            return QH::ParserResult::Error;
        }

        emit profileIsUpdated();

        return QH::ParserResult::Processed;

    } else if (H_16<QH::PKG::UserMember>() == pkg.hdr.command) {
        QH::PKG::UserMember obj(pkg);

        LocalUser user(&obj);
        auto localuser = db()->getObject(user)->clone().dynamicCast<LocalUser>();
        localuser->setToken(obj.token());
        localuser->setOnline(true);

        if (!db()->saveObject(localuser.data())) {
            return QH::ParserResult::Error;
        }

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
        const LocalUser* localUser = getLocalUser(userId);
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

bool HanoiClient::userDatarequest(const QString &userId) {
    UserDataRequest request;
    request.setId(userId);

    return sendData(&request, _serverAddress);
}

const LocalUser *HanoiClient::getLocalUser(const QString &userId) const {
    LocalUser request;
    request.setId(userId);

    if (!db()) {
        return nullptr;
    }

    return db()->getObject(request);
}

QSharedPointer<LocalUser>
HanoiClient::getEditableLocalUser(const QString &userId) {
    if (auto edit = getLocalUser(userId)) {
        return edit->clone<LocalUser>();
    }

    return {nullptr};
}

ProfileData HanoiClient::defaultProfile() const {
    return ProfileData("User");
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

QString HanoiClient::currentUserName() const {
    return _currentUserName;
}

ProfileData HanoiClient::currentProfile() {

    auto userData = getLocalUser(_currentUserName);

    if (userData)
        return userData->userData();

    return defaultProfile();
}

bool HanoiClient::addProfile(const ProfileData &profile) {
    auto userData = getEditableLocalUser(_currentUserName);

    if (userData) {
        return false;
    }

    LocalUser user;
    user.setId(profile.name());

    if (auto database = db()) {
        return database->saveObject(&user);
    }

    return false;

}

bool HanoiClient::updateProfile(const ProfileData &profile) {
    auto userData = getEditableLocalUser(_currentUserName);

    if (userData.isNull()) {
        return false;
    }

    userData->setUserData(profile);

    if (!db()->saveObject(userData.data())) {
        return false;
    }

    if (userData->online()) {
        UserData data;
        data.setId(profile.name());
        data.setUserData(profile);

        return sendData(&data, _serverAddress);
    }

    return true;
}


bool HanoiClient::login(const QString &login, const QString &rawPassword) {

    auto user = getLocalUser(login);

    if (!user || !user->isValid()) {
        emit requestError("User '" + login + "' is not exists");
        return false;
    }

    _currentUserName = login;

    if (user->online() && !p_login(login, hashgenerator(rawPassword.toLatin1()))) {
        return false;
    }

    return true;

}

bool HanoiClient::registerUser(const QString &login, const QString &rawPassword) {
    auto user = getLocalUser(login);

    if (user) {
        emit requestError("User '" + login + "' is alredy exists");
        return false;
    }

    return p_signIn(login, hashgenerator(rawPassword.toLatin1()));
}

bool HanoiClient::registerOflineUser(const QString &login) {
    LocalUser user;
    user.setId(login);

    return db()->saveObject(&user);
}

bool HanoiClient::removeUser(const QString &login) {
    auto user = getLocalUser(login);
    QH::PKG::AuthRequest request;
    request.setId(user->getId());
    request.setRequest(UserRequestType::Remove);

    return sendData(&request, _serverAddress);
}

void HanoiClient::connectToServer(const QH::HostAddress &host) {
    addNode(host);
    _serverAddress = host;
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


