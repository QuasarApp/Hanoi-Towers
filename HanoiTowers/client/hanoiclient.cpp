/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiclient.h"
#include <qmlnotifyservice.h>
#include <user.h>
#include <userdata.h>
#include <sqldbcache.h>

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

    } else if (H_16<QH::PKG::User>() == pkg.hdr.command) {
        QH::PKG::User obj(pkg);

        if (db()->saveObject(&obj)) {
            return QH::ParserResult::Error;
        }

    }

    return QH::ParserResult::NotProcessed;
}

QStringList HanoiClient::SQLSources() const {
//    return {

//    };
}

void HanoiClient::handleError(const QString &error) {
    QmlNotificationService::NotificationService::getService()->setNotify(
                tr("Jnline error"), error, "",
                QmlNotificationService::NotificationData::Error);
}


