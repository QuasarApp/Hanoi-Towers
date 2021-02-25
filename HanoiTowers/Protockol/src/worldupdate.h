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
#include <itoken.h>

class WorldUpdate: public QH::PKG::AbstractData, public QH::IToken
{
public:
    WorldUpdate();

    bool isValid() const override;
    const QH::AccessToken &getSignToken() const override;

    // StreamBase interface
    const QSet<UserPreview> &getDataAddUpdate() const;
    void setDataAddUpdate(const QSet<UserPreview> &dataAddUpdate);

    const QSet<UserPreview>& getDataRemove() const;
    void setDataRemove(const QSet<UserPreview> &dataRemove);

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

private:
    QSet<UserPreview> _dataAddUpdate;
    QSet<UserPreview> _dataRemove;

    QH::AccessToken _token;
};

#endif // WORLDUPDATE_H
