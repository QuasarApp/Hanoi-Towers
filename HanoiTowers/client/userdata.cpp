/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "userdata.h"
#include "profiledata.h"

UserData::UserData():
    QH::PKG::DBObject("UsersData"),
    _userData("") {

}

UserData::UserData(const QH::Package &from):
    UserData() {
    fromPakcage(from);
}

UserData::UserData(const ProfileData &from): UserData() {
    _userData = from;
}

bool UserData::copyFrom(const QH::PKG::AbstractData *other) {
    if (!AbstractData::copyFrom(other))
        return false;

    auto otherObject = dynamic_cast<const UserData*>(other);
    if (!otherObject)
        return false;

    _userData = otherObject->_userData;
    return true;
}

QH::PKG::DBObject *UserData::createDBObject() const {
    return new UserData();
}

QH::PKG::PrepareResult UserData::prepareSaveQuery(QSqlQuery &q) const {
    return QH::PKG::PrepareResult::Disabled;
}

QDataStream &UserData::fromStream(QDataStream &stream) {
    AbstractData::fromStream(stream);
    stream >> _userData;
    return stream;
}

QDataStream &UserData::toStream(QDataStream &stream) const {
    AbstractData::toStream(stream);
    stream << _userData;
    return stream;
}

QH::BaseId UserData::generateId() const {
    return {};
}
