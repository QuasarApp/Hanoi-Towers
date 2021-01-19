#include "useravatar.h"

UserAvatar::UserAvatar(): QH::PKG::DBObject("Avatars") {

}

bool UserAvatar::copyFrom(const QH::PKG::AbstractData *other) {
    if (!DBObject::copyFrom(other))
        return false;

    auto otherObject = dynamic_cast<const UserAvatar*>(other);
    if (!otherObject)
        return false;

    _image = otherObject->_image;
    _userId = otherObject->_userId;

    return true;
}

QH::PKG::DBObject *UserAvatar::createDBObject() const {
    return create<UserAvatar>();
}

bool UserAvatar::fromSqlRecord(const QSqlRecord &q) {
    if (!DBObject::fromSqlRecord(q)) {
        return false;
    }

    _image = q.value("data").toByteArray();
    _userId = q.value("user_id").toString();

    return isValid();
}

bool UserAvatar::isValid() const {
    return DBObject::isValid() && _userId.size() && !_image.isEmpty();
}

QDataStream &UserAvatar::fromStream(QDataStream &stream) {
    DBObject::toStream(stream);
    stream >> _image;
    stream >> _userId;

    return stream;
}

QDataStream &UserAvatar::toStream(QDataStream &stream) const {
    DBObject::toStream(stream);
    stream << _image;
    stream << _userId;

    return stream;
}

QH::PKG::DBVariantMap UserAvatar::variantMap() const {
    return {{primaryKey(),  {primaryValue(),      QH::PKG::MemberType::PrimaryKeyAutoIncrement}},
            {"user_id",     {_userId,             QH::PKG::MemberType::InsertUpdate}},
            {"data",        {_image,              QH::PKG::MemberType::InsertUpdate}}};
}

QString UserAvatar::primaryKey() const {
    return "id";
}

QString UserAvatar::userId() const {
    return _userId;
}

void UserAvatar::setUserId(const QString &userId) {
    _userId = userId;
}

QByteArray UserAvatar::image() const {
    return _image;
}

void UserAvatar::setImage(const QByteArray &image) {
    _image = image;
}
