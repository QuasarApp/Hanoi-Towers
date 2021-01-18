/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef RECORDLISTMODEL_H
#define RECORDLISTMODEL_H
#include <QAbstractTableModel>
#include <QMap>
#include <qqml.h>
#include "userpreview.h"

class RecordListModel: public QAbstractListModel
{
    Q_OBJECT

public:

    enum RecordListModelRoles {
        Username = Qt::UserRole,
        Record,
        UserId
    };

    RecordListModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void updateSourceItem(const UserPreview& data);
    void removeSourceItem(const QString& id);

public slots:
    void setSource(const QList<UserPreview> &data);

private:
    QList<UserPreview>  _data;


    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // RECORDLISTMODEL_H
