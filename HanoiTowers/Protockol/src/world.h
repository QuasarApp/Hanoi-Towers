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
    World(const QString& worldName = "World");

    bool fromSqlRecord(const QSqlRecord &q) override;
    QH::PKG::DBObject *createDBObject() const override;
    void clear() override;
    bool isValid() const override;
    const QH::AccessToken &getSignToken() const override;
    unsigned int subscribeId() const override;
    bool copyFrom(const QH::PKG::AbstractData *other) override;

    void setSignToken(const QH::AccessToken &token) override;

    QSet<UserPreview> getData() const;
    void setData(const QSet<UserPreview> &data);
    bool applyUpdate(const WorldUpdate& update);
    unsigned int getWorldVersion() const;
    const QString &getBestUserId() const;

protected:
    QH::PKG::DBVariantMap variantMap() const override;
    QString condition() const override;

    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

    virtual void bestUserChanged(const QString &bestUser);
    void setBestUserId(const QString &value);

private:
    bool softUpdate(const WorldUpdate& update);
    bool softUpdatePrivate(const QSet<UserPreview> &);
    bool hardUpdate(const WorldUpdate& update);

    QSet<UserPreview>::ConstIterator fullSearch() const;

    QSet<UserPreview> _data;
    QH::AccessToken _token;
    unsigned int _subscribeId;
    unsigned int _worldVersion = 0;
    QString _bestUserId;


};

#endif // WORLD_H
