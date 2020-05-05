#ifndef TERMINAL_H
#define TERMINAL_H

#include <patronum.h>

class Terminal : public Patronum::Controller
{
public:
    Terminal();

    // Controller interface
protected:
    QString defaultInstallLocation();
};

#endif // TERMINAL_H
