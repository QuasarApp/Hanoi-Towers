/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "recordlistmodel.h"

RecordListModel::RecordListModel(QObject *parent):
    QAbstractListModel(parent) {

}

int RecordListModel::rowCount(const QModelIndex &) const {
    return _data.size();
}

QVariant RecordListModel::data(const QModelIndex &index, int role) const {
    if (rowCount(index) <= index.row()) {
        return {};
    }

    auto iten = _data.value(index.row());

    if (role == Username) {
        return iten.userName;
    }

    if (role == Record) {
        return iten.record;
    }

    if (role == UserId) {
        return iten.id;
    }

    return "Not Supported";
}

void RecordListModel::setSource(const QList<UserPreview> &data) {
    beginResetModel();
    _data = data;
    endResetModel();
}

void RecordListModel::updateSourceItem(const UserPreview &data) {
    auto row = _data.indexOf(data);
    if (row >= 0) {
        emit dataChanged(index(row, 0), index(row, 0));
    } else {
        beginInsertRows({}, _data.size(), _data.size());
        _data.push_back(data);
        endInsertRows();
    }
}

void RecordListModel::removeSourceItem(const QString &id) {
    auto row = _data.indexOf(id);
    if (row < 0)
        return;

    beginRemoveRows({}, row, row);
    _data.removeAt(row);
    endRemoveRows();
}

QHash<int, QByteArray> RecordListModel::roleNames() const {
    auto result = QAbstractListModel::roleNames();

    result[Username]    = "username";
    result[Record]      = "record";
    result[UserId]      = "userid";

    return result;
}

