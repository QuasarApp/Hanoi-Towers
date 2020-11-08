/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "profiledata.h"

void ProfileData::setOnline(bool onlineProfile) {
    if (onlineProfile) {
        emit onlineRequest(name());
    } else {
        emit onlineChanged(onlineProfile);
    }
}

void ProfileData::setRecord(int rec) {
    if (_record == rec)
        return;

    _record = rec;
    emit recordChanged(rec);
}

void ProfileData::setAvatarHash(int avatarHash) {
    if (_avatarHash == avatarHash)
        return;

    _avatarHash = avatarHash;
    emit avatarHashChanged(_avatarHash);
}

ProfileData::ProfileData(const QByteArray &userID):
    QObject(nullptr) {
    _userId = userID;
}

ProfileData::ProfileData(const ProfileData &oither) {
    operator=(oither);
}

ProfileData::~ProfileData() = default;

QObject *ProfileData::gameState() {
    return &_state;
}

QString ProfileData::name() const {
    return _name;
}

int ProfileData::record() const {
    return _record;
}

bool ProfileData::isOnline() const {
    return _online;
}

void ProfileData::setName(const QString &name) {
    if (_name != name) {
        _name = name;
        emit nameChanged(_name);
    }
}

QDataStream &ProfileData::fromStream(QDataStream &stream) {
    stream >> _name >>
            _userId >>
            _record >>
            _online >>
            _state;

    emit gameStateChanged(&_state);
    emit onlineChanged(_online);
    emit recordChanged(_record);
    emit nameChanged(_name);
    emit userIdChanged(_userId);

    return stream;
}

QDataStream &ProfileData::toStream(QDataStream &stream) const {
    return stream << _name <<
                     _userId <<
                     _record <<
                     _online <<
                     _state;
}

ProfileData &ProfileData::operator =(const ProfileData &right) {
    this->fromBytes(right.toBytes());
    return *this;
}

QString ProfileData::userId() const{
    return _userId;
}

QByteArray ProfileData::userIdRaw() const {
    return _userId;
}

int ProfileData::avatarHash() const {
    return _avatarHash;
}
