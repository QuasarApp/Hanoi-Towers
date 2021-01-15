/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef PROFILEDATA_H
#define PROFILEDATA_H
#include "gamestate.h"

struct HANOITOWERSPROTOCOL_EXPORT ProfileData {
    GameState _state;
    QString _name;
    int _record = 0;
    bool _online = false;
    int _avatarHash;
};



#endif // PROFILEDATA_H
