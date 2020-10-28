#ifndef LOCALUSER_H
#define LOCALUSER_H

#include "dbobject.h"
#include <accesstoken.h>
#include <profiledata.h>


class LocalUser: public QH::PKG::DBObject
{
public:
    LocalUser();

    bool copyFrom(const QH::PKG::AbstractData *other) override;
    bool fromSqlRecord(const QSqlRecord &q) override;
    bool isValid() const override;

    // DBObject interface
    bool online() const;
    void setOnline(bool online);

    QString userName() const;
    void setUserName(const QString &userName);

    QByteArray hashPassword() const;
    void setHashPassword(const QByteArray &hashPassword);

    QH::AccessToken token() const;
    void setToken(const QH::AccessToken &token);

    ProfileData userData() const;
    void setUserData(const ProfileData &userData);

    int updateTime() const;
    void setUpdateTime(int updateTime);

protected:
    QH::PKG::DBVariantMap variantMap() const override;
    QH::BaseId generateId() const override;
    QH::PKG::DBObject *createDBObject() const override;

private:
    bool _online = false;
    QByteArray _hashPassword;
    QH::AccessToken _token;
    ProfileData _userData;
    int _updateTime;


    // AbstractData interface
public:
};

#endif // LOCALUSER_H
