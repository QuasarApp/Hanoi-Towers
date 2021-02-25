#ifndef ONLINERATING_H
#define ONLINERATING_H

#include <dbobject.h>
#include "hanoitowersprotockol_global.h"


class HANOITOWERSPROTOCOL_EXPORT OnlineRating: public QH::PKG::DBObject
{
public:
    OnlineRating();

    // DBObject interface
    QH::PKG::DBObject *createDBObject() const override;

protected:
    QString primaryKey() const override;
};

#endif // ONLINERATING_H
