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

class WorldUpdate: public QH::PKG::AbstractData, public QH::IToken,
        public QH::PKG::ISubscribableData
{
public:
    WorldUpdate(const QString& worldName = "World");

    bool isValid() const override;
    const QH::AccessToken &getSignToken() const override;
    unsigned int subscribeId() const override;
    void setSignToken(const QH::AccessToken &) override;

    // StreamBase interface
    const QSet<UserPreview> &getDataAddUpdate() const;
    void setDataAddUpdate(const QSet<UserPreview> &dataAddUpdate);

    const QSet<UserPreview>& getDataRemove() const;
    void setDataRemove(const QSet<UserPreview> &dataRemove);

    unsigned int getWorldVersion() const;
    void setWorldVersion(unsigned int worldVersion);

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

private:

    QSet<UserPreview> _dataAddUpdate;
    QSet<UserPreview> _dataRemove;
    QH::AccessToken _token;
    unsigned int _subscribeId;
    unsigned int _worldVersion = 0;


};

#endif // WORLDUPDATE_H
