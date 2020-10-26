#ifndef LOCALUSER_H
#define LOCALUSER_H

#include "user.h"

class LocalUser: public QH::PKG::User
{
public:
    LocalUser();

    bool copyFrom(const QH::PKG::AbstractData *other);
    bool fromSqlRecord(const QSqlRecord &q);

    // DBObject interface
    bool online() const;
    void setOnline(bool online);

protected:
    QH::PKG::DBVariantMap variantMap() const;
private:
    bool _online = false;
};

#endif // LOCALUSER_H
