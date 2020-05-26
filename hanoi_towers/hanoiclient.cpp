/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiclient.h"
#include <qmlnotifyservice.h>
#include <userdatarequest.h>

HanoiClient::HanoiClient():
    NP::Client(REMOTE_HOST, REMOTE_PORT) {
    connectClient();

    connect(this, &HanoiClient::requestError,
            this, &HanoiClient::handleError);
}

void HanoiClient::handleError(const QString &error) {
    QmlNotificationService::NotificationService::getService()->setNotify(
                tr("Jnline error"), error, "",
                QmlNotificationService::NotificationData::Error);
}


