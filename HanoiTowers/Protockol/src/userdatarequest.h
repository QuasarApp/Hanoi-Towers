#ifndef USERDATAREQUEST_H
#define USERDATAREQUEST_H

#include "userdata.h"

#include <request.h>

class HANOITOWERSPROTOCOL_EXPORT UserDataRequest: public UserData, public QH::Request
{
public:

    enum Request {
        Get = 0
    };

    UserDataRequest();
    UserDataRequest(const QH::Package& package);

    unsigned char getRequestCmd() const override;
    bool isValid() const override;
};

#endif // USERDATAREQUEST_H
