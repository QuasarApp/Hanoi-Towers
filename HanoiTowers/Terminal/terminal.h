#ifndef TERMINAL_H
#define TERMINAL_H

#include <patronum.h>

class Terminal : public Patronum::Controller
{
public:
    Terminal();

    // Controller interface
protected:

    void handleError(Patronum::ControllerError);
};

#endif // TERMINAL_H
