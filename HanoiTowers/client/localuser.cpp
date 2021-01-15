/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "localuser.h"
#include <accesstoken.h>

using MT = QH::PKG::MemberType;

LocalUser::LocalUser():
    QH::PKG::DBObject("Users")
{

}

LocalUser::LocalUser(const QH::PKG::DBObject *other ):LocalUser() {
    copyFrom(other);
}

bool LocalUser::copyFrom(const QH::PKG::AbstractData *other) {
    if (!QH::PKG::DBObject::copyFrom(other))
        return false;

    auto otherObject = dynamic_cast<const LocalUser*>(other);
    if (!otherObject)
        return false;

    this->_hashPassword = otherObject->_hashPassword;
    this->_token = otherObject->_token;
    this->_userData._avatarHash = otherObject->_userData._avatarHash;
    this->_userData._name = otherObject->_userData._name;
    this->_userData._online = otherObject->_userData._online;
    this->_userData._record = otherObject->_userData._record;
    this->_userData._state = otherObject->_userData._state;

    this->_updateTime = otherObject->_updateTime;

    emit prfileDataChanged();

    return true;
}

bool LocalUser::fromSqlRecord(const QSqlRecord &q) {
    if(!DBObject::fromSqlRecord(q)) {
        return false;
    }

    setHashPassword(q.value("passwordHash").toByteArray());
    setToken(QH::AccessToken{q.value("token").toByteArray()});

    setToken(QH::AccessToken{q.value("token").toByteArray()});
    setToken(QH::AccessToken{q.value("token").toByteArray()});
    setToken(QH::AccessToken{q.value("token").toByteArray()});
    setToken(QH::AccessToken{q.value("token").toByteArray()});

    setUpdateTime(q.value("updateTime").toInt());


    return LocalUser::isValid();
}

bool LocalUser::isValid() const {
    return DBObject::isValid() && _updateTime > 1603891116;
}

GameState *LocalUser::gameState() {
    return &_userData._state;
}

QString LocalUser::userId() const {
    return getId().toString();
}

QString LocalUser::name() const {
    return _userData._name;
}

int LocalUser::record() const {
    return _userData._record;
}

bool LocalUser::isOnline() const {
    return _userData._online;
}

int LocalUser::avatarHash() const {
    return _userData._avatarHash;
}

void LocalUser::setName(const QString &name) {
    if (_userData._name == name)
        return;

    _userData._name = name;
    emit nameChanged(name);
}

QH::PKG::DBVariantMap LocalUser::variantMap() const {
    return {{primaryKey(),         {getId(),                            MT::PrimaryKey}},
            {"passwordHash",       {_hashPassword,                      MT::InsertUpdate}},
            {"token",              {_token.toBytes(),                   MT::InsertUpdate}},

            {"gameState",          {_userData._state.toBytes(),         MT::InsertUpdate}},
            {"userName",           {_userData._name,                    MT::InsertUpdate}},
            {"points",             {_userData._record,                  MT::InsertUpdate}},
            {"fOnline",            {_userData._online,                  MT::InsertUpdate}},

            {"userAvatar",         {_userData._avatarHash,              MT::InsertUpdate}},
            {"updateTime",         {static_cast<int>(time(nullptr)),    MT::InsertUpdate}}};

}

QH::PKG::DBObject *LocalUser::createDBObject() const {
    return create<LocalUser>();
}

QString LocalUser::primaryKey() const {
    return "id";
}

int LocalUser::updateTime() const {
    return _updateTime;
}

void LocalUser::setUpdateTime(int updateTime) {
    _updateTime = updateTime;
}

const ProfileData* LocalUser::userData() const {
    return &_userData;
}

ProfileData *LocalUser::userData() {
    return &_userData;
}

void LocalUser::setUserData(const ProfileData &userData) {
    _userData = userData;
}

QH::AccessToken LocalUser::token() const {
    return _token;
}

void LocalUser::setToken(const QH::AccessToken &token) {
    _token = token;
}

QByteArray LocalUser::hashPassword() const {
    return _hashPassword;
}

void LocalUser::setHashPassword(const QByteArray &hashPassword) {
    _hashPassword = hashPassword;
}

bool LocalUser::online() const {

    return _userData._online;
}

void LocalUser::setOnline(bool online) {
    _userData._online = online;

    if (online) {
        emit onlineRequest(name());
    } else {
        emit onlineChanged(online);
    }
}

void LocalUser::setRecord(int record) {
    if (_userData._record == record)
        return;

    _userData._record = record;
    emit recordChanged(record);
}

void LocalUser::setAvatarHash(int avatarHash) {
    if (_userData._avatarHash == avatarHash)
        return;

    _userData._avatarHash = avatarHash;
    emit avatarChanged(avatarHash);

}
