/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "profiledata.h"

ProfileData::ProfileData() {

}

ProfileData::ProfileData(const ProfileData &other) {
    ProfileData::operator=(other);
}

QDataStream &ProfileData::fromStream(QDataStream &stream) {

    stream >> _state;
    stream >> _name;
    stream >> _record;
    stream >> _online;
    stream >> _avatarHash;

    return stream;
}

QDataStream &ProfileData::toStream(QDataStream &stream) const {
    stream << _state;
    stream << _name;
    stream << _record;
    stream << _online;
    stream << _avatarHash;
    return stream;

}

ProfileData &ProfileData::operator=(const ProfileData &right) {
    return static_cast<ProfileData&>(StreamBase::operator=(right));
}
