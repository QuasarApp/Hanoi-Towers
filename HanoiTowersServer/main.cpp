#include "hanoiservice.h"

int main(int argc, char *argv[])
{
    HanoiService server(argc, argv);
    return server.exec();
}
