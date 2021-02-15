/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiserver.h"
#include "hanoiservice.h"
#include <quasarapp.h>

HanoiService::HanoiService(int argc, char *argv[]):
    Patronum::Service<QCoreApplication>(argc, argv, "HanoiService") {

    if (!QuasarAppUtils::Params::isEndable("fileLog"))
        QuasarAppUtils::Params::setArg("fileLog", "/var/log/HanoiService.log");
}

HanoiService::~HanoiService() {
    HanoiService::onStop();
}

void HanoiService::onStart() {
    if (!_server) {
        _server = new HanoiServer();
    }
}

void HanoiService::onStop() {
    if (_server) {
        _server->softDelete();
        _server = nullptr;
    }

    Service::onStop();
}

void HanoiService::handleReceive(const QList<Patronum::Feature> &data) {

    QList<Patronum::Feature> notSupported;
    for (const auto& i: data) {
        if (i.cmd() == "ping") {
            sendResuylt("Pong");
        } else if (i.cmd() == "Players") {
            //_server->
        } else {
            notSupported += i;
        }
    }

    Patronum::Service<QCoreApplication>::handleReceive(notSupported);
}

QList<Patronum::Feature> HanoiService::supportedFeatures() {
    QList<Patronum::Feature> data;

    data << Patronum::Feature("ping");
    data << Patronum::Feature("Players");

    return data;
}
