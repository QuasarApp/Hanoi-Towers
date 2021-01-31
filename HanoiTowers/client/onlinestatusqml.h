#ifndef ONLINESTATUSQML_H
#define ONLINESTATUSQML_H
#include <QObject>


enum class OnlineStatus: int {
    Offline,
    Connecting,
    Connected,
    Loginning,
    Loggined
};

class OnlineStatusQml
{
    Q_GADGET

    Q_PROPERTY(int offline READ offline)
    Q_PROPERTY(int connecting READ connecting)
    Q_PROPERTY(int connected READ connected)
    Q_PROPERTY(int loginning READ loginning)
    Q_PROPERTY(int loggined READ loggined)

public:
    OnlineStatusQml();

    Q_INVOKABLE int offline() const;
    Q_INVOKABLE int connecting() const;
    Q_INVOKABLE int connected() const;
    Q_INVOKABLE int loginning() const;
    Q_INVOKABLE int loggined() const;
};

Q_DECLARE_METATYPE(OnlineStatusQml)
Q_DECLARE_METATYPE(OnlineStatus)

#endif // ONLINESTATUSQML_H
