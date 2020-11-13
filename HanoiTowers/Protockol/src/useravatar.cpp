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

    return isValid();
}

bool UserAvatar::isValid() const {
    return DBObject::isValid();
}

QDataStream &UserAvatar::fromStream(QDataStream &stream) {
    DBObject::toStream(stream);
    stream >> _image;
    return stream;
}

QDataStream &UserAvatar::toStream(QDataStream &stream) const {
    DBObject::toStream(stream);
    stream << _image;
    return stream;
}

QH::PKG::DBVariantMap UserAvatar::variantMap() const {
    return {{"data", {_image,      QH::PKG::MemberType::InsertUpdate}}};
}

QString UserAvatar::primaryKey() const {
    return "id";
}

QByteArray UserAvatar::image() const {
    return _image;
}

void UserAvatar::setImage(const QByteArray &image) {
    _image = image;
}
