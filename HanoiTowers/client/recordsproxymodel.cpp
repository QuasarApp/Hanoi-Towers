/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/


#include "recordsproxymodel.h"
#include "recordlistmodel.h"

RecordsProxyModel::RecordsProxyModel(QObject *parent):
    QSortFilterProxyModel(parent) {

}

QVariant RecordsProxyModel::data(const QModelIndex &index, int role) const {

    if (role == RecordListModel::Row) {
        return index.row();
    }

    return QSortFilterProxyModel::data(index, role);
}
