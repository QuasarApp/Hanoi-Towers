#include "localuser.h"
#include <accesstoken.h>

using MT = QH::PKG::MemberType;

LocalUser::LocalUser():
    QH::PKG::DBObject("Users"),
    _userData("") {

}

bool LocalUser::copyFrom(const QH::PKG::AbstractData *other) {
    if (!QH::PKG::DBObject::copyFrom(other))
        return false;

    auto otherObject = dynamic_cast<const LocalUser*>(other);
    if (!otherObject)
        return false;

    this->_online = otherObject->_online;
    this->_hashPassword = otherObject->_hashPassword;
    this->_token = otherObject->_token;
    this->_userData = otherObject->_userData;

    return true;
}

bool LocalUser::fromSqlRecord(const QSqlRecord &q) {
    if(!DBObject::fromSqlRecord(q)) {
        return false;
    }

    setHashPassword(q.value("passwordHash").toByteArray());
    setToken(QH::AccessToken{q.value("token").toByteArray()});
    setOnline(q.value("onlineUser").toBool());
    setUserData({q.value("userdata").toByteArray()});

    return LocalUser::isValid();
}

QH::PKG::DBVariantMap LocalUser::variantMap() const {
    return {{"passwordHash",       {_hashPassword,        MT::InsertUpdate}},
            {"token",              {_token.toBytes(),     MT::InsertUpdate}},
            {"userdata",           {_userData.toBytes(),  MT::InsertUpdate}},
            {"onlineUser",         {_online,              MT::InsertUpdate}}};

}

QH::BaseId LocalUser::generateId() const {
    return getId();
}

QH::PKG::DBObject *LocalUser::createDBObject() const {
    return create<LocalUser>();
}

ProfileData LocalUser::userData() const {
    return _userData;
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
    return _online;
}

void LocalUser::setOnline(bool online) {
    _online = online;
}
