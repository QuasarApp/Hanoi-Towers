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
    Patronum::Service<QCoreApplication>(argc, argv) {
}

HanoiService::~HanoiService() {
    if (_server) {
        _server->softDelete();
        _server = nullptr;
    }
}

void HanoiService::onStart() {
    if (!QuasarAppUtils::Params::isEndable("fileLog"))
        QuasarAppUtils::Params::setArg("fileLog", "/var/log/HanoiService.log");

    if (!_server) {
        _server = new HanoiServer();
    }
}

void HanoiService::onStop() {
    Service::onStop();
}

bool HanoiService::handleReceive(const Patronum::Feature &data) {

    if (data.cmd() == "ping") {
        return sendResuylt("Pong");

    } else if (data.cmd() == "status") {
        return sendResuylt(_server->getWorkState().toString());

    } else if (data.cmd() == "log") {
        return workWithLogFile(data);

    } else if (data.cmd() == "logLvl") {
        return workWithLogLvl(data);
    }

    return false;
}

QSet<Patronum::Feature> HanoiService::supportedFeatures() {
    QSet<Patronum::Feature> data;

    data << Patronum::Feature("ping", "", "This is simple test command. Server should be responce \"Pong\"");
    data << Patronum::Feature("status","", "Return current status of the server.");
    data << Patronum::Feature("log", "path/to/newLog/file", "Peint path to log file or sets new path if you set in in arguments", "-log [ath/to/new/log/file");
    data << Patronum::Feature("logLvl", "[0-3]", "Sets new verbose log level.");

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

bool HanoiService::workWithLogFile(const Patronum::Feature &data) {

    auto path = data.arg();

    if (path.isEmpty()) {
        auto fileLog = QuasarAppUtils::Params::getArg("fileLog");

        if (fileLog.isEmpty()) {
            return sendResuylt("The service works without log file");
        }

        return sendResuylt("The logs availabel in " + fileLog);
    }

    if (!changeFileLogPath(path)) {
        return false;
    }

    return sendResuylt("The logs file sets to " + QuasarAppUtils::Params::getArg("fileLog"));
}

bool HanoiService::workWithLogLvl(const Patronum::Feature &data) {
    auto lvl = data.arg();

    if (lvl.isEmpty()) {
        auto lvl = QuasarAppUtils::Params::getVerboseLvl();
        return sendResuylt("The service logs lvl =" + QString::number(lvl));
    }

    QuasarAppUtils::Params::setArg("verbose", lvl);

    return sendResuylt("The service logs lvl =" + lvl);
}
