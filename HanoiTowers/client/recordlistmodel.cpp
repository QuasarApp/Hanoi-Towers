#include "recordlistmodel.h"

RecordListModel::RecordListModel(QObject *parent):
    QAbstractTableModel(parent) {

}

int RecordListModel::rowCount(const QModelIndex &) const {
    return _data.size();
}

int RecordListModel::columnCount(const QModelIndex &) const {
    return 3;
}

QVariant RecordListModel::data(const QModelIndex &index, int role) const {
    if (rowCount(index) <= index.row()) {
        return {};
    }

    if (columnCount(index) <= index.row()) {
        return {};
    }

    auto iten = _data.begin() + index.row();

    if (role == Qt::DisplayRole) {

        switch (index.column()) {
        case 0: {
            return iten.key();
        }
        case 1: {
            return iten.value().record;
        }

        default:
            return "This column not supported of the RecordListModel";
        }
    }

    if (role == RecordListModel::RecordListModelRoles::OnlineRole) {

        if (index.column() == 2) {
            return iten.value().online;
        }
        return -1;
    }

    return {};
}

void RecordListModel::setSource(const QMap<QString, UserPreview> &data) {
    beginResetModel();
    _data = data;
    endResetModel();
}

void RecordListModel::updateSourceItem(const UserPreview &data) {
    int row = std::distance(_data.begin(), _data.find(data.UserName));
    if (row >= 0) {
        emit dataChanged(index(row, 0), index(row, 3));
    } else {
        beginInsertRows({}, _data.size(), _data.size());
        _data.insert(data.UserName, data);
        endInsertRows();
    }
}

void RecordListModel::removeSourceItem(const QString &name) {
    int row = std::distance(_data.begin(), _data.find(name));

    if (row < 0)
        return;

    beginRemoveRows({}, row, row);
    _data.remove(name);
    endRemoveRows();
}

QHash<int, QByteArray> RecordListModel::roleNames() const {
    auto hash = QAbstractTableModel::roleNames();

    hash[RecordListModel::RecordListModelRoles::OnlineRole] = "online";
    hash[RecordListModel::RecordListModelRoles::RemoveRole] = "remove";

    return hash;
}
