/*
 * Copyright (C) 2018-2021 QuasarApp.
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
#include <basenodeinfo.h>
#include "config.h"
#include "basedefines.h"
#include "badrequest.h"
#include "hanoierrorcodes.h"

HanoiServer::HanoiServer() {
    QString address = "";
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

    registerPackageType<UserData>();
    registerPackageType<UserDataRequest>();

}

QH::ParserResult HanoiServer::parsePackage(const QSharedPointer<QH::PKG::AbstractData> &pkg,
                                           const QH::Header &pkgHeader,
                                           const QH::AbstractNodeInfo *sender) {

    auto parentResult = SingleServer::parsePackage(pkg, pkgHeader, sender);
    if (parentResult != QH::ParserResult::NotProcessed) {
        return parentResult;
    }

    if (H_16<UserData>() == pkg->cmd()) {
        auto obj = pkg.staticCast<UserData>();

        auto requesterId = getSender(sender, obj.data());

        auto opResult = updateIfNotExistsCreateObject(requesterId, obj);
        if (opResult != QH::DBOperationResult::Allowed) {
            return QH::ParserResult::Error;
        }

        return QH::ParserResult::Processed;

    } else if (H_16<UserDataRequest>() == pkg->cmd()) {
        auto obj = pkg.staticCast<UserDataRequest>();

        if (!workWirthUserData(obj.data(), sender, &pkgHeader)) {
            return QH::ParserResult::Error;
        }

        return QH::ParserResult::Processed;

    }

    return QH::ParserResult::NotProcessed;
}

QStringList HanoiServer::SQLSources() const {
    return SingleServer::SQLSources() << ":/HanoiTowersSql/sql/database.sql";
}

QVariantMap HanoiServer::defaultDbParams() const {
    return QH::DataBaseNode::defaultDbParams();
}

bool HanoiServer::workWirthUserData(const UserData *obj,
                                    const QH::AbstractNodeInfo *sender,
                                    const QH::Header *oldHeader) {

    QSharedPointer<DBObject> userData;

    if (getObject(getSender(sender, obj), *obj, userData) != QH::DBOperationResult::Allowed) {
        if (oldHeader) {
            badRequest(sender->networkAddress(), *oldHeader,
                       {
                           ErrorCodes::PermissionDenied,
                           "The user don not have a premsion of the requested object."
                       });
        }

        return false;
    }

    return sendData(userData.data(), sender->networkAddress());
}

void HanoiServer::nodeConfirmend(QH::AbstractNodeInfo *node) {
    if (auto baseNode = dynamic_cast<QH::BaseNodeInfo*>(node)) {
        UserDataRequest request;

        request.setId(baseNode->id());

        workWirthUserData(&request, node);

    }
}
