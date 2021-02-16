/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/


#include "onlinestatusqml.h"

OnlineStatusQml::OnlineStatusQml()
{

}

int OnlineStatusQml::offline() const {
    return static_cast<int>(OnlineStatus::Dissconnected);
}

int OnlineStatusQml::connecting() const {
    return static_cast<int>(OnlineStatus::Connecting);

}

int OnlineStatusQml::connected() const {
    return static_cast<int>(OnlineStatus::Connected);

}

int OnlineStatusQml::loginning() const {
    return static_cast<int>(OnlineStatus::Loginning);

}

int OnlineStatusQml::loggined() const {
    return static_cast<int>(OnlineStatus::Logined);

}
