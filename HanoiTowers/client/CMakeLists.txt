#
# Copyright (C) 2018-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)


set(CURRENT_PROJECT "${PROJECT_NAME}Client")


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_CPP
    "*.cpp" "*.qrc"
)

add_executable(${CURRENT_PROJECT} ${SOURCE_CPP})
target_link_libraries(${CURRENT_PROJECT} PRIVATE QmlNotyfyService HanoiTowersProtockol LoginView Credits)
target_include_directories(${CURRENT_PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


set(LANGS ${CMAKE_CURRENT_SOURCE_DIR}/languages/en.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ru.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ja.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/tr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ua.ts)


prepareQM(${CURRENT_PROJECT} ${CMAKE_CURRENT_SOURCE_DIR} "${LANGS}")
