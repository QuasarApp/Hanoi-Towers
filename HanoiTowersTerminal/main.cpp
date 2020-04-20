#include "terminal.h"

int main(int argc, char *argv[])
{
    Terminal terminal;
    terminal.send(argc, argv);
    return terminal.waitForResponce();
}
