#
# Copyright (C) 2018-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)

include(../Heart/QuasarAppLib/CMake/ProjectOut.cmake)
include(../Heart/QuasarAppLib/CMake/ccache.cmake)
include(../Heart/QuasarAppLib/CMake/Version.cmake)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_subdirectory(Protockol)
add_subdirectory(client)
add_subdirectory(Server)
add_subdirectory(Terminal)

