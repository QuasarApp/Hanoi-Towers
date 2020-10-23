#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)


set(CURRENT_PROJECT "${PROJECT_NAME}Protockol")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DHANOITOWERSPROTOCOL)

file(GLOB SOURCE_CPP
    "src/*.cpp"
    "src/Private/*.cpp"
    "src/Private/*.qrc"
)

add_library(${CURRENT_PROJECT} SHARED ${SOURCE_CPP})
target_link_libraries(${CURRENT_PROJECT} PUBLIC Heart)
target_include_directories(${CURRENT_PROJECT} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${CURRENT_PROJECT} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Private")

setVersionForTarget(${CURRENT_PROJECT} ${PRODUCT_VER_Mj} ${PRODUCT_VER_Mn} ${PRODUCT_VER_Re})
