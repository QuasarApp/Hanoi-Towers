/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef USERDATA_H
#define USERDATA_H

#include <dbobject.h>
#include <profiledata.h>

class UserData: public QH::PKG::DBObject
{
public:
    UserData();
    UserData(const QH::Package& from);
    UserData(const ProfileData& from);

    bool copyFrom(const AbstractData *other) override;
    QH::PKG::DBObject *createDBObject() const override;
    QH::PKG::PrepareResult prepareSaveQuery(QSqlQuery &q) const override;

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;

    QH::BaseId generateId() const override;

private:
    ProfileData _userData;
};

#endif // USERDATA_H
