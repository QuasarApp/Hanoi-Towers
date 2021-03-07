#ifndef USERDATA_H
#define USERDATA_H
#include "profiledata.h"

#include <dbobject.h>
#include <itoken.h>

using namespace QH::PKG;

class HANOITOWERSPROTOCOL_EXPORT UserData: public DBObject, public QH::IToken
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

    const QH::AccessToken &getSignToken() const override;

    void setName(const QString& name);
    QString name() const;

    ProfileData userData() const;
    void setUserData(const ProfileData &userData);

    int updateTime() const;
    void setUpdateTime(int updateTime);

    void setSignToken(const QH::AccessToken &token) override;


protected:
    QDataStream &fromStream(QDataStream &stream) override;
    QDataStream &toStream(QDataStream &stream) const override;
    DBVariantMap variantMap() const override;
    QString primaryKey() const override;

private:
    ProfileData _userData;
    QH::AccessToken _token;
    int _updateTime;

};

#endif // USERDATA_H
