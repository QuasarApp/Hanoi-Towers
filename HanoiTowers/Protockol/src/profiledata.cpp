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

ProfileData::ProfileData(const QString &name):
    QObject(nullptr) {
    setName(name);
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
    _name = name;
}

QDataStream &ProfileData::fromStream(QDataStream &stream) {
    return stream >> _name >> _record >> _online >> _state;
}

QDataStream &ProfileData::toStream(QDataStream &stream) const {
    return stream << _name << _record << _online << _state;
}

ProfileData &ProfileData::operator =(const ProfileData &right) {
    this->fromBytes(right.toBytes());
    return *this;
}