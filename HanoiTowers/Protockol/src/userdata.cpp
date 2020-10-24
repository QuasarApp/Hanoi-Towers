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

QH::PKG::DBObject *UserData::createDBObject() const {
    return new UserData();
}

QH::PKG::PrepareResult UserData::prepareSaveQuery(QSqlQuery &q) const {
    QString queryString = "INSERT INTO %0(%1) VALUES (%3) "
                          "ON CONFLICT(id) DO UPDATE SET %2";
    queryString = queryString.arg(tableName());
    queryString = queryString.arg("id, name, points, userdata");
    queryString = queryString.arg("points=:points, userdata=:userdata");

    QString values;

    values += "'" + getId().toBase64() + "', ";
    values += "'" + _userData.name() + "', ";
    values += ":points, ";
    values += ":userdata";

    queryString = queryString.arg(values);

    if (q.prepare(queryString)) {

        q.bindValue(":points", _userData.record());
        q.bindValue(":userdata", _userData.toBytes());

        return PrepareResult::Success;
    }

    QuasarAppUtils::Params::log("Query:" + queryString,
                                QuasarAppUtils::Error);

    return PrepareResult::Fail;
}

PrepareResult UserData::prepareSelectQuery(QSqlQuery &q) const {
    return DBObject::prepareSelectQuery(q);
}

bool UserData::fromSqlRecord(const QSqlRecord &q) {
    if (!DBObject::fromSqlRecord(q)) {
        return false;
    }

    _userData.fromBytes(q.value("userdata").toByteArray());
    return isValid();
}

PrepareResult UserData::prepareRemoveQuery(QSqlQuery &q) const {
    return DBObject::prepareRemoveQuery(q);
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

void UserData::clear() {

}
