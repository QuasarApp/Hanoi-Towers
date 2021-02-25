/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef WORLD_H
#define WORLD_H

#include "userpreview.h"

#include <QSet>
#include <dbobjectset.h>
#include <itoken.h>

class WorldUpdate;

class World: public QH::PKG::DBObjectSet, public QH::IToken
{
public:
    World();

    bool fromSqlRecord(const QSqlRecord &q) override;
    QH::PKG::DBObject *createDBObject() const override;
    void clear() override;
    bool isValid() const override;
    const QH::AccessToken &getSignToken() const override;


    void setToken(const QH::AccessToken &token);


    QSet<UserPreview> getData() const;
    void setData(const QSet<UserPreview> &data);

    void applyUpdate(const WorldUpdate& update);


protected:
    QH::PKG::DBVariantMap variantMap() const override;
    QString condition() const override;

    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

private:
    QSet<UserPreview> _data;

    QH::AccessToken _token;
};

#endif // WORLD_H
