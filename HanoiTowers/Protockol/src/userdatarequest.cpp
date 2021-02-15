#include "userdatarequest.h"

UserDataRequest::UserDataRequest()
{

}

UserDataRequest::UserDataRequest(const QH::Package &package):
    UserData(package) {

}

unsigned char UserDataRequest::getRequestCmd() const {
    return Request::Get;
}

bool UserDataRequest::isValid() const {
    return getId().isValid();
}
