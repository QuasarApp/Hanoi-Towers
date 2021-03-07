#include "userdata.h"
#include "quasarapp.h"

#include <QSqlQuery>

UserData::UserData():
    QH::PKG::DBObject("UsersData") {

}

UserData::UserData(const QH::Package &from):
    UserData() {
    fromPakcage(from);
}

UserData::UserData(const ProfileData &from): UserData() {
    _userData = from;
}

bool UserData::copyFrom(const QH::PKG::AbstractData *other) {
    if (!DBObject::copyFrom(other))
        return false;

    auto otherObject = dynamic_cast<const UserData*>(other);
    if (!otherObject)
        return false;

    _userData = otherObject->_userData;
    _updateTime = otherObject->_updateTime;
    _token = otherObject->_token;

    return true;
}

const QH::AccessToken &UserData::getSignToken() const {
    return _token;
}

void UserData::setName(const QString &name) {
    _userData._name = name;
}

QString UserData::name() const {
    return _userData._name;
}

QH::PKG::DBObject *UserData::createDBObject() const {
    return create<UserData>();
}

bool UserData::fromSqlRecord(const QSqlRecord &q) {
    if (!DBObject::fromSqlRecord(q)) {
        return false;
    }

    _userData._avatar = q.value("userAvatar").toByteArray();
    _userData._name = q.value("userName").toString();
    _userData._record = q.value("points").toInt();
    _userData._state.fromBytes(q.value("gameState").toByteArray());

    setUpdateTime(q.value("updateTime").toInt());

    return isValid();
}

bool UserData::isValid() const {
    return DBObject::isValid() && _userData._name.size() > 0 && _updateTime > 1604255995;
}

QDataStream &UserData::fromStream(QDataStream &stream) {
    DBObject::fromStream(stream);
    stream >> _userData;
    stream >> _updateTime;
    stream >> _token;

    return stream;
}

QDataStream &UserData::toStream(QDataStream &stream) const {
    DBObject::toStream(stream);
    stream << _userData;
    stream << _updateTime;
    stream << _token;

    return stream;
}

DBVariantMap UserData::variantMap() const {
    return {{primaryKey(),  {getId(),                   QH::PKG::MemberType::PrimaryKey}},
            {"userName",    {_userData._name,           QH::PKG::MemberType::InsertUpdate}},
            {"points",      {_userData._record,         QH::PKG::MemberType::InsertUpdate}},
            {"updateTime",  {_updateTime,               QH::PKG::MemberType::InsertUpdate}},
            {"gameState",   {_userData._state.toBytes(),QH::PKG::MemberType::InsertUpdate}},
            {"userAvatar",  {_userData._avatar,         QH::PKG::MemberType::InsertUpdate}}};
}

QString UserData::primaryKey() const {
    return "id";
}

void UserData::setSignToken(const QH::AccessToken &token) {
    _token = token;
}

int UserData::updateTime() const {
    return _updateTime;
}

void UserData::setUpdateTime(int updateTime){
    _updateTime = updateTime;
}

ProfileData UserData::userData() const {
    return _userData;
}

void UserData::setUserData(const ProfileData &userData) {
    _userData = userData;
}

void UserData::clear() {

}
