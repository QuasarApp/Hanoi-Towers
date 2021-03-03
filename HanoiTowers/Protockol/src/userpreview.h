/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef USERPREVIEW_H
#define USERPREVIEW_H

#include <QString>
#include <streambase.h>
#include <QSharedPointer>

struct UserPreview: public QH::StreamBase {
    explicit UserPreview();
    explicit UserPreview(const QString& id);

    QString id;
    QString userName;
    int record;

    friend bool operator==(const UserPreview& left, const UserPreview& right);

    // StreamBase interface
protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;
};

uint qHash(const UserPreview& input);

Q_DECLARE_METATYPE(UserPreview)
Q_DECLARE_METATYPE(QSharedPointer<UserPreview>)

#endif // USERPREVIEW_H
