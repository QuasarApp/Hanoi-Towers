/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/


#ifndef RECORDSPROXYMODEL_H
#define RECORDSPROXYMODEL_H

#include <QSortFilterProxyModel>

class RecordsProxyModel : public QSortFilterProxyModel
{
public:
    explicit RecordsProxyModel(QObject *parent = nullptr);
};

#endif // RECORDSPROXYMODEL_H
