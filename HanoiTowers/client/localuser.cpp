#include "localuser.h"
#include <accesstoken.h>

using MT = QH::PKG::MemberType;
LocalUser::LocalUser() {

}

bool LocalUser::copyFrom(const QH::PKG::AbstractData *other) {
    if (!QH::PKG::User::copyFrom(other))
        return false;

    auto otherObject = dynamic_cast<const LocalUser*>(other);
    if (!otherObject)
        return false;

    this->_online = otherObject->_online;

    return true;
}

bool LocalUser::fromSqlRecord(const QSqlRecord &q) {
    if(!DBObject::fromSqlRecord(q)) {
        return false;
    }

    setAuthenticationData(q.value("passwordHash").toByteArray());
    setToken(QH::AccessToken{q.value("token").toByteArray()});
    setOnline(q.value("onlineUser").toBool());

    return LocalUser::isValid();
}

QH::PKG::DBVariantMap LocalUser::variantMap() const {
    return {{"passwordHash",       {authenticationData(), MT::InsertUpdate}},
            {"token",              {token().toBytes(),    MT::InsertUpdate}},
            {"onlineUser",         {_online,              MT::InsertUpdate}}};

}

bool LocalUser::online() const
{
    return _online;
}

void LocalUser::setOnline(bool online)
{
    _online = online;
}
