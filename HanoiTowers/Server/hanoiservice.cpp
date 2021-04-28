/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiserver.h"
#include "hanoiservice.h"
#include <quasarapp.h>

#include <QFileInfo>
#include <QDir>

HanoiService::HanoiService(int argc, char *argv[]):
    Patronum::Service<QCoreApplication>(argc, argv, "HanoiTowersService") {

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

bool HanoiService::handleReceive(const Patronum::Feature &data) {

    if (data.cmd() == "ping") {
        sendResuylt("Pong");
    } else if (data.cmd() == "state") {
        sendResuylt(_server->getWorkState().toString());
    } else if (data.cmd() == "log") {
        auto path = data.arg();

        if (!changeFileLogPath(path)) {
            return false;
        }
        sendResuylt("The logs now availabel it" + path);
    } else if (data.cmd() == "logLvl") {
        auto lvl = data.arg();

        if (lvl.isEmpty()) {
            sendResuylt("In current time logs print with level " + lvl);
        } else {
            QuasarAppUtils::Params::setArg("verbose", lvl);
            sendResuylt("The logs now print with level " + lvl);
        }
    }


    return true;
}

QSet<Patronum::Feature> HanoiService::supportedFeatures() {
    QSet<Patronum::Feature> data;

    data << Patronum::Feature("ping");
    data << Patronum::Feature("state");
    data << Patronum::Feature("log");
    data << Patronum::Feature("logLvl");

    return data;
}

bool HanoiService::changeFileLogPath(const QString& path) {
    QFileInfo file(path);
    if (file.dir().isReadable()) {
        QuasarAppUtils::Params::setArg("fileLog", file.absoluteFilePath());
        return true;
    }

    return false;
}
