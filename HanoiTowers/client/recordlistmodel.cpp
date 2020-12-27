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

    auto iten = std::next(_data.begin(), index.row());

    if (role == Username) {
        return iten.value().userName;
    }

    if (role == Record) {
        return iten.value().record;
    }

    return "Not Supported";
}

void RecordListModel::setSource(const QMap<QString, UserPreview> &data) {
    beginResetModel();
    _data = data;
    endResetModel();
}

void RecordListModel::updateSourceItem(const UserPreview &data) {
    int row = std::distance(_data.begin(), _data.find(data.userName));
    if (row >= 0) {
        emit dataChanged(index(row, 0), index(row, 0));
    } else {
        beginInsertRows({}, _data.size(), _data.size());
        _data.insert(data.userName, data);
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
    auto result = QAbstractListModel::roleNames();

    result[Username]    = "username";
    result[Record]      = "record";

    return result;
}

