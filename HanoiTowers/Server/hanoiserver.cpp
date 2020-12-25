/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiserver.h"
#include <QDir>
#include <QNetworkInterface>
#include <QCoreApplication>
#include <userdata.h>
#include <usermember.h>
#include <userdatarequest.h>
#include "config.h"
#include "basedefines.h"
#include "badrequest.h"
#include "hanoierrorcodes.h"

HanoiServer::HanoiServer() {
    QString address = DEFAULT_ADDRESS;
    unsigned short port = DEFAULT_HANOI_PORT;

    if (QuasarAppUtils::Params::isEndable("address")) {
        auto addressList = QuasarAppUtils::Params::getStrArg("address").split(":");
        if (address.size() != 2) {

            QuasarAppUtils::Params::log("invalid address params",
                                               QuasarAppUtils::Error);
            QCoreApplication ::exit(2);

        }

        address = addressList.first();
        port = static_cast<decltype (port)>(addressList.last().toInt());
    }

    if (!run(address, port)) {
        QuasarAppUtils::Params::log("fail to run server",
                                           QuasarAppUtils::Error);
        QCoreApplication ::exit(3);

    }
}

QH::ParserResult HanoiServer::parsePackage(const QH::Package &pkg,
                                           const QH::AbstractNodeInfo *sender) {

    auto parentResult = SingleServer::parsePackage(pkg, sender);
    if (parentResult != QH::ParserResult::NotProcessed) {
        return parentResult;
    }

    if (H_16<UserData>() == pkg.hdr.command) {
        auto obj = QSharedPointer<UserData>::create(pkg);

        auto requesterId = getSender(sender, obj.data());

        auto opResult = updateIfNotExistsCreateObject(requesterId, obj);
        if (opResult != QH::DBOperationResult::Allowed) {
            return QH::ParserResult::Error;
        }

        return QH::ParserResult::Processed;

    } else if (H_16<UserDataRequest>() == pkg.hdr.command) {
        UserDataRequest obj(pkg);
        auto requesterId = getSender(sender, &obj);
        const QH::PKG::DBObject* userData;

        if (getObject(requesterId, obj, &userData) != QH::DBOperationResult::Allowed) {
            badRequest(sender->networkAddress(), pkg.hdr,
                       {
                           ErrorCodes::PermissionDenied,
                           "The user don not have a premsion of the requested object."
                       });

            return QH::ParserResult::Error;
        };

        if (!sendData(userData, sender->networkAddress(), &pkg.hdr)) {
            return QH::ParserResult::Error;
        }

        return QH::ParserResult::Processed;

    }

    return QH::ParserResult::NotProcessed;
}

QStringList HanoiServer::SQLSources() const {
    return DataBaseNode::SQLSources() << "qrc:/HanoiTowersSql/sql/database.sql";
}

QVariantMap HanoiServer::defaultDbParams() const {
    return QH::DataBaseNode::defaultDbParams();
}

bool HanoiServer::workWirthUserData(const UserData *obj,
                                    const QH::AbstractNodeInfo *sender) {

    auto requesterId = getSender(sender, obj);
    const DBObject *userData;

    if (getObject(requesterId, *obj, &userData) != QH::DBOperationResult::Allowed) {
        return false;
    }

    return sendData(userData, sender->networkAddress());
}
