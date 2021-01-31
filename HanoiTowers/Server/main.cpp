/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("HanoiTowers Server"); // <--
    QCoreApplication::setOrganizationName("QuasarApp"); // <--
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--

    HanoiService server(argc, argv);
    return server.exec();
}
