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


    bool isValid() const override;
    bool copyFrom(const AbstractData *other) override;

    void setName(const QString& name);
    QString name() const;

    ProfileData userData() const;
    void setUserData(const ProfileData &userData);

    int updateTime() const;
    void setUpdateTime(int updateTime);

protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;
    DBVariantMap variantMap() const override;
    QString primaryKey() const override;

private:
    ProfileData _userData;
    int _updateTime;

};

#endif // USERDATA_H
