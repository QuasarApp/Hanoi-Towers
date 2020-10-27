#ifndef USERDATA_H
#define USERDATA_H
#include "profiledata.h"

#include <dbobject.h>

using namespace QH::PKG;

class HANOITOWERSPROTOCOL_EXPORT UserData: public DBObject
{
public:
    UserData();
    UserData(const QH::Package &from);
    UserData(const ProfileData &from);


    void clear() override;
    DBObject *createDBObject() const override;
    //sql
    bool fromSqlRecord(const QSqlRecord &q) override;
    QPair<QString, QString> altarnativeKey() const override;


    bool isValid() const override;
    bool copyFrom(const AbstractData *other) override;

    void setName(const QString& name);
    ProfileData userData() const;
    void setUserData(const ProfileData &userData);

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;
    QH::BaseId generateId() const override;
    DBVariantMap variantMap() const override;

private:
    ProfileData _userData;

};

#endif // USERDATA_H
