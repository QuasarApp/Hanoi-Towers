#include "world.h"
#include "worldupdate.h"

World::World():
QH::PKG::DBObjectSet("UsersData") {


}

bool World::fromSqlRecord(const QSqlRecord &q) {
    UserPreview data;
    data.id = q.value("userID").toString();

    data.userName = q.value("userName").toString();
    data.record = q.value("points").toInt();

    _data.insert(data);

    return true;
}

QH::PKG::DBObject *World::createDBObject() const {
    return create<World>();
}

void World::clear() {
    _data.clear();
}

bool World::isValid() const {
    return true;
}

const QH::AccessToken &World::getSignToken() const {
    return _token;
}

QH::PKG::DBVariantMap World::variantMap() const {
    return {{"id",          {}},
            {"points",      {}},
            {"userName",    {}}};
}

QString World::condition() const {
    return "";
}

QDataStream &World::fromStream(QDataStream &stream) {
    DBObjectSet::fromStream(stream);

    stream >> _data;
    stream >> _token;

    return stream;
}

QDataStream &World::toStream(QDataStream &stream) const {
    DBObjectSet::toStream(stream);

    stream << _data;
    stream << _token;

    return stream;
}

QSet<UserPreview> World::getData() const {
    return _data;
}

void World::setData(const QSet<UserPreview> &data) {
    _data = data;
}

void World::applyUpdate(const WorldUpdate &update) {
    _data += update.getDataAddUpdate();
    _data -= update.getDataRemove();

}

void World::setToken(const QH::AccessToken &token) {
    _token = token;
}
