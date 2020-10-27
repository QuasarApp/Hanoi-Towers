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

        return QH::ParserResult::Processed;

    } else if (H_16<QH::PKG::UserMember>() == pkg.hdr.command) {
        QH::PKG::UserMember obj(pkg);

        auto localuser = db()->getObject(obj)->cloneRaw();
        localuser->copyFrom(&obj);

        if (db()->saveObject(localuser)) {
            return QH::ParserResult::Error;
        }

    }

    return QH::ParserResult::NotProcessed;
}

QStringList HanoiClient::SQLSources() const {
    return {
        ":/sql/sql/database.sql"
    };
}

void HanoiClient::handleError(const QString &error) {
    QmlNotificationService::NotificationService::getService()->setNotify(
                tr("Jnline error"), error, "",
                QmlNotificationService::NotificationData::Error);
}

bool HanoiClient::login(const QString& userId) {
    QH::PKG::AuthRequest request;
    request.setId(userId);
    request.setRequest(QH::PKG::UserRequestType::Login);

    return sendData(&request, _serverAddress);
}

bool HanoiClient::signIn(const QString &userId) {
    QH::PKG::AuthRequest request;
    request.setId(userId);
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

ProfileData HanoiClient::defaultProfile() const {
    return ProfileData("User");
}

QString HanoiClient::currentUserName() const {
    return _currentUserName;
}

void HanoiClient::setCurrentUserName(const QString &currentUserName) {
    _currentUserName = currentUserName;
}

ProfileData HanoiClient::currentProfile() {

    auto userData = getLocalUser(_currentUserName);

    if (userData)
        return userData->userData();

    return defaultProfile();
}

void HanoiClient::connectToServer(const QH::HostAddress &host) {
    addNode(host);
    _serverAddress = host;
}


