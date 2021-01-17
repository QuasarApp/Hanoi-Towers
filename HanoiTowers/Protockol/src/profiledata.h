/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef PROFILEDATA_H
#define PROFILEDATA_H
#include "gamestate.h"

class HANOITOWERSPROTOCOL_EXPORT ProfileData : public QH::StreamBase {
public:

    ProfileData();
    ProfileData(const ProfileData& other);

    GameState _state;
    QString _name;
    int _record = 0;
    bool _online = false;
    int _avatarHash;

    ProfileData& operator= (const ProfileData& right);

    // StreamBase interface
protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

};



#endif // PROFILEDATA_H
