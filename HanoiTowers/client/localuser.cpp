#include "localuser.h"
#include <accesstoken.h>

using MT = QH::PKG::MemberType;

LocalUser::LocalUser():
    QH::PKG::DBObject("Users"),
    _userData("") {

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
    this->_userData = otherObject->_userData;
    this->_updateTime = otherObject->_updateTime;

    return true;
}

bool LocalUser::fromSqlRecord(const QSqlRecord &q) {
    if(!DBObject::fromSqlRecord(q)) {
        return false;
    }

    setHashPassword(q.value("passwordHash").toByteArray());
    setToken(QH::AccessToken{q.value("token").toByteArray()});
    _userData.fromBytes(q.value("userdata").toByteArray());
    setUpdateTime(q.value("updateTime").toInt());


    return LocalUser::isValid();
}

bool LocalUser::isValid() const {
    return DBObject::isValid() && _updateTime > 1603891116;
}

QH::PKG::DBVariantMap LocalUser::variantMap() const {
    return {{primaryKey(),         {getId(),                            MT::PrimaryKey}},
            {"passwordHash",       {_hashPassword,                      MT::InsertUpdate}},
            {"token",              {_token.toBytes(),                   MT::InsertUpdate}},
            {"userdata",           {_userData.toBytes(),                MT::InsertUpdate}},
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
    return _userData.isOnline();
}

void LocalUser::setOnline(bool online) {
    _userData.setOnline(online);
}
