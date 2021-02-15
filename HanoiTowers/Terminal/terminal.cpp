/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "terminal.h"
#include <QCoreApplication>

Terminal::Terminal():Patronum::Controller("HanoiService",
                                          QCoreApplication::applicationDirPath() + "/../ServerHanoiTowers.sh") {

}

void Terminal::handleError(Patronum::ControllerError err) {
    Patronum::Controller::handleError(err);
    QCoreApplication::exit(static_cast<int>(err));
}
