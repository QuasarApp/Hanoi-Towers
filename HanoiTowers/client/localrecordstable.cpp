/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "localrecordstable.h"

#include <QDataStream>
#include <profiledata.h>

LocalRecordsTable::LocalRecordsTable():
    QH::PKG::DBObjectSet("Users") {

}

bool LocalRecordsTable::fromSqlRecord(const QSqlRecord &q) {

    UserPreview data;
    data.id = q.value("id").toString();

    data.userName = q.value("userName").toString();
    data.record = q.value("points").toInt();

    _data[data.id] = data;

    return true;
}

QH::PKG::DBObject *LocalRecordsTable::createDBObject() const {
    return create<LocalRecordsTable>();
}

QH::PKG::DBVariantMap LocalRecordsTable::variantMap() const {
    return {{"id",          {}},
            {"points",      {}},
            {"userName",    {}}};
}

QString LocalRecordsTable::condition() const {
    return "";
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
    return true;
}
