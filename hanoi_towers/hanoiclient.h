#ifndef HANOICLIENT_H
#define HANOICLIENT_H

#define REMOTE_HOST "quasarapp.ddns.net"
#define REMOTE_PORT 7788

#include <client.h>
class HanoiClient: public NP::Client
{
public:
    HanoiClient();
};

#endif // HANOICLIENT_H
