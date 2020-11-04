#include "localrecordstable.h"

#include <QDataStream>
#include <profiledata.h>

LocalRecordsTable::LocalRecordsTable():
    QH::PKG::DBObjectSet("Users") {

}

bool LocalRecordsTable::fromSqlRecord(const QSqlRecord &q) {

    UserPreview data;
    ProfileData profile(q.value("id").toByteArray());
    profile.fromBytes(q.value("userdata").toByteArray());

    data.userName = profile.name();
    data.id = profile.userId().toLatin1();
    data.record = profile.record();

    _data[data.id] = data;

    return true;
}

QDataStream &LocalRecordsTable::fromStream(QDataStream &stream) {
    QH::PKG::DBObject::fromStream(stream);

    stream >> _data;
    return stream;
}

QDataStream &LocalRecordsTable::toStream(QDataStream &stream) const {
    QH::PKG::DBObject::toStream(stream);

    stream << _data;

    return stream;

}

QH::PKG::DBVariantMap LocalRecordsTable::variantMap() const {
    return {{"id",          {}},
            {"userdata",    {}}};
}

const QMap<QString, UserPreview> &LocalRecordsTable::data() const {
    return _data;
}

void LocalRecordsTable::setData(const QMap<QString, UserPreview> &data) {
    _data = data;
}

void LocalRecordsTable::clear() {
    _data.clear();
}

bool LocalRecordsTable::isValid() const{
    return _data.size();
}
