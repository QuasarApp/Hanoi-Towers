#
# Copyright (C) 2018-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)


set(CURRENT_PROJECT ${PROJECT_NAME})


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_CPP
    "*.cpp" "*.qrc"
)

if (ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/android CACHE INTERNAL "")
    add_library(${CURRENT_PROJECT} ${SOURCE_CPP})
else()
    add_executable(${CURRENT_PROJECT} ${SOURCE_CPP})
endif()

target_link_libraries(${CURRENT_PROJECT} PRIVATE QmlNotyfyService HanoiTowersProtockol LoginView Credits)
target_include_directories(${CURRENT_PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


set(LANGS ${CMAKE_CURRENT_SOURCE_DIR}/languages/en.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ru.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ja.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/tr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ua.ts)


prepareQM(${CURRENT_PROJECT} ${CMAKE_CURRENT_SOURCE_DIR} "${LANGS}")

if (ANDROID)
    set(QT_ANDROID_APPLICATION_BINARY "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
    addDeployAPK("Android" "${CMAKE_BINARY_DIR}/android_deployment_settings.json" "digitalface" "${SIGN_PATH}/DigitalFaceMobily.keystore" "${SIGN_STORE_PASSWORD}" "${TARGET_DIR}")
else()
    # Desctop deploying
    addDeployFromCustomFile("Client" "${CMAKE_SOURCE_DIR}/Deploy/Client.json")

#    if (UNIX)
#        #addDeployQIF("Client" ${INSTALLER_DIR} ${TARGET_DIR} "${INSTALLER_DIR}/config/configLinux.xml")
#        #addDeploySnap("Client" ${TARGET_DIR})

#        #addReleaseSnap("Client")

#    endif()
endif()

#addReleaseQif("Client" ${DATA_DIR} ${TARGET_DIR})

