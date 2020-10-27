#include "userdata.h"
#include "quasarapp.h"

#include <QSqlQuery>

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
    if (!DBObject::copyFrom(other))
        return false;

    auto otherObject = dynamic_cast<const UserData*>(other);
    if (!otherObject)
        return false;

    _userData = otherObject->_userData;
    return true;
}

void UserData::setName(const QString &name) {
    _userData.setName(name);
}

QH::PKG::DBObject *UserData::createDBObject() const {
    return new UserData();
}

bool UserData::fromSqlRecord(const QSqlRecord &q) {
    if (!DBObject::fromSqlRecord(q)) {
        return false;
    }

    _userData.fromBytes(q.value("userdata").toByteArray());
    return isValid();
}

QPair<QString, QString> UserData::altarnativeKey() const {
    return {"name", _userData.name()};
}

bool UserData::isValid() const {
    return DBObject::isValid() && _userData.name().size() > 0;
}

QDataStream &UserData::fromStream(QDataStream &stream) {
    DBObject::fromStream(stream);
    stream >> _userData;
    return stream;
}

QDataStream &UserData::toStream(QDataStream &stream) const {
    DBObject::toStream(stream);
    stream << _userData;
    return stream;
}

QH::BaseId UserData::generateId() const {
    return {};
}

DBVariantMap UserData::variantMap() const {
    return {{"name",        {_userData.name(),      QH::PKG::MemberType::InsertOnly}},
            {"points",      {_userData.record(),    QH::PKG::MemberType::InsertUpdate}},
            {"userdata",    {_userData.toBytes(),   QH::PKG::MemberType::InsertUpdate}}};
}

ProfileData UserData::userData() const {
    return _userData;
}

void UserData::setUserData(const ProfileData &userData) {
    _userData = userData;
}

void UserData::clear() {

}
