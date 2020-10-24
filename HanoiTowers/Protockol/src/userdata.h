#ifndef USERDATA_H
#define USERDATA_H
#include "profiledata.h"

#include <dbobject.h>

using namespace QH::PKG;

class UserData: public DBObject
{
public:
    UserData();
    UserData(const QH::Package &from);
    UserData(const ProfileData &from);


    void clear() override;
    DBObject *createDBObject() const override;
    //sql
    PrepareResult prepareSaveQuery(QSqlQuery &q) const override;
    PrepareResult prepareSelectQuery(QSqlQuery &q) const override;
    bool fromSqlRecord(const QSqlRecord &q) override;
    PrepareResult prepareRemoveQuery(QSqlQuery &q) const override;
    QPair<QString, QString> altarnativeKey() const override;


    bool isValid() const override;
    bool copyFrom(const AbstractData *other) override;

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;
    QH::BaseId generateId() const override;

private:
    ProfileData _userData;
};

#endif // USERDATA_H
