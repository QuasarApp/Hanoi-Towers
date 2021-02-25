#include "world.h"

World::World():
QH::PKG::DBObjectSet("UsersData") {


}

bool World::fromSqlRecord(const QSqlRecord &q) {
    UserPreview data;
    data.id = q.value("userID").toString();

    data.userName = q.value("userName").toString();
    data.record = q.value("points").toInt();

    _data.push_back(data);

    return true;
}

QH::PKG::DBObject *World::createDBObject() const {

}

void World::clear() {

}

bool World::isValid() const {

}

QH::PKG::DBVariantMap World::variantMap() const {

}

QString World::condition() const {

}
