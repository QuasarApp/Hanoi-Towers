/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef WORLD_H
#define WORLD_H

#include "userpreview.h"

#include <dbobjectset.h>

class World: public QH::PKG::DBObjectSet
{
public:
    World();

    bool fromSqlRecord(const QSqlRecord &q) override;
    QH::PKG::DBObject *createDBObject() const override;
    void clear() override;
    bool isValid() const override;

protected:
    QH::PKG::DBVariantMap variantMap() const override;
    QString condition() const override;

private:
    QList<UserPreview> _data;

};

#endif // WORLD_H
