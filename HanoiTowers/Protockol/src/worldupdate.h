/*
 * Copyright (C) 2021-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/


#ifndef WORLDUPDATE_H
#define WORLDUPDATE_H

#include "userpreview.h"

#include <QSet>
#include <abstractdata.h>
#include <isubscribabledata.h>
#include <itoken.h>

#include "hanoitowersprotockol_global.h"

class HANOITOWERSPROTOCOL_EXPORT WorldUpdate: public QH::PKG::AbstractData, public QH::IToken,
        public QH::PKG::ISubscribableData
{
public:
    WorldUpdate(const QString& worldName = "World");

    bool isValid() const override;
    const QH::AccessToken &getSignToken() const override;
    unsigned int subscribeId() const override;
    void setSignToken(const QH::AccessToken &) override;

    // StreamBase interface
    const QHash<QString, UserPreview> &getDataAddUpdate() const;
    void setDataAddUpdate(const QHash<QString, UserPreview> &dataAddUpdate);

    const QSet<QString> &getDataRemove() const;
    void setDataRemove(const QSet<QString> &dataRemove);

    unsigned int getWorldVersion() const;
    void setWorldVersion(unsigned int worldVersion);

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

private:

    QHash<QString, UserPreview> _dataAddUpdate;
    QSet<QString> _dataRemove;
    QH::AccessToken _token;
    unsigned int _subscribeId;
    unsigned int _worldVersion = 0;


};

Q_DECLARE_METATYPE(WorldUpdate)
Q_DECLARE_METATYPE(QSharedPointer<WorldUpdate>)
#endif // WORLDUPDATE_H
