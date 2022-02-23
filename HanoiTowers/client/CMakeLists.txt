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
    "*.cpp" "*.h" "*.qrc"
)

if (ANDROID)

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
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/uk.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/es.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/fr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/de.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/zh.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/pl.ts)


prepareQM(${CURRENT_PROJECT} ${CMAKE_CURRENT_SOURCE_DIR} "${LANGS}")

if (ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")

    set(ENV{ANDROID_API_VERSION} 31)
    set(ANDROID_API_VERSION $ENV{ANDROID_API_VERSION})
    set(OPENSSL_ROOT_PATH "$ENV{OPENSSL_ROOT_DIR}")

    set(HANOI_EXTRA_LIBS Heart
                         ${PROJECT_NAME}Protockol
                         QuasarApp
                         LoginView
                         Credits
                         QmlNotyfyService)

    find_package(QT NAMES Qt6 Qt5 COMPONENTS AndroidExtras REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AndroidExtras REQUIRED)

    addDeploySignedAPK(
        ${CURRENT_PROJECT}
        "${CMAKE_CURRENT_LIST_DIR}/android"
        "digitalface"
        "${SIGPATH}/DigitalFaceMobily.keystore"
        "${SIGPASS_HANOI}"
        "${TARGET_DIR}"
        "${HANOI_EXTRA_LIBS}")

    target_link_libraries(${CURRENT_PROJECT} PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)

    if (HANOI_ADMOD)
        target_link_libraries(${CURRENT_PROJECT} PRIVATE QtAndroidTools)

    endif()

    set(manifest_file "${CMAKE_CURRENT_SOURCE_DIR}/android/AndroidManifest.xml")
    configure_file("${manifest_file}.in" ${manifest_file} @ONLY)

    set(gradle_file "${CMAKE_CURRENT_SOURCE_DIR}/android/build.gradle")
    configure_file("${gradle_file}.in" ${gradle_file} @ONLY)


    file(GLOB java_files
       "android/src/com/quasarapp/androidtools/*.java"
       "android/*.xml"
       "android/*.in"
       "android/*.gradle"
       "android/gradlew"
       "android/gradle.*"

    )

    add_custom_target(${name}Android
        SOURCES ${java_files}
    )

else()
    # Desctop deploying
    addDeployFromCustomFile("Client" "${CMAKE_SOURCE_DIR}/Deploy/Client.json")

    if (UNIX)
        #addDeployQIF("Client" ${INSTALLER_DIR} ${TARGET_DIR} "${INSTALLER_DIR}/config/configLinux.xml")
        addDeploySnap("Client" ${TARGET_DIR})

        #addReleaseSnap("Client")

    endif()
endif()

#addReleaseQif("Client" ${DATA_DIR} ${TARGET_DIR})

