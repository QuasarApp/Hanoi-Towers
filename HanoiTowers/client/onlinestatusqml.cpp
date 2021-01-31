#include "onlinestatusqml.h"

OnlineStatusQml::OnlineStatusQml()
{

}

int OnlineStatusQml::offline() const {
    return static_cast<int>(OnlineStatus::Offline);
}

int OnlineStatusQml::connecting() const {
    return static_cast<int>(OnlineStatus::Connecting);

}

int OnlineStatusQml::connected() const {
    return static_cast<int>(OnlineStatus::Connected);

}

int OnlineStatusQml::loginning() const {
    return static_cast<int>(OnlineStatus::Loginning);

}

int OnlineStatusQml::loggined() const {
    return static_cast<int>(OnlineStatus::Loggined);

}
