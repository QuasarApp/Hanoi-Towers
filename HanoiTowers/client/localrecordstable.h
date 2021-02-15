/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef LOCALRECORDSTABLE_H
#define LOCALRECORDSTABLE_H

#include "userpreview.h"

#include <dbobjectset.h>

class LocalRecordsTable: public QH::PKG::DBObjectSet
{
public:
    LocalRecordsTable();

    bool fromSqlRecord(const QSqlRecord &q) override;
    QH::PKG::DBObject *createDBObject() const override;

    const QList<UserPreview>& data() const;
    void setData(const QList<UserPreview>& data);
    void clear() override;
    bool isValid() const override;

protected:
    QH::PKG::DBVariantMap variantMap() const override;
    QString condition() const override;

private:
    QList<UserPreview> _data;
};

#endif // LOCALRECORDSTABLE_H
