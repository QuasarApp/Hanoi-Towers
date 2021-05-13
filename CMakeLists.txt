#
# Copyright (C) 2018-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)
project(HanoiTowers)

set(BUILD_SHARED_LIBS ON)


include(submodules/Heart/QuasarAppLib/CMake/QuasarApp.cmake)
include(submodules/Heart/QuasarAppLib/CMake/Version.cmake)
initAll()

if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
    if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
        return()
    endif()
endif()

if (NOT DEFINED ONLINE_FUNCTIONS)
    set(ONLINE_FUNCTIONS OFF)
endif()

if(ONLINE_FUNCTIONS)
    add_definitions(-DONLINE_FUNCTIONS)
else()
    set(HEART_SSL OFF)
endif()

if (NOT DEFINED HANOI_TESTS)
    set(HANOI_TESTS ON)

    if (ANDROID)
        set(HANOI_TESTS OFF)
    endif()
endif()

if (NOT DEFINED HANOI_ADMOD)
    set(HANOI_ADMOD ON)

    if (ANDROID)
        set(HANOI_ADMOD ON)
    endif()
endif()

if (HANOI_ADMOD)
    add_definitions(-DHANOI_ADMOD)
endif()

if (NOT DEFINED HANOI_SERVER)
    set(HANOI_SERVER ON)

    if (ANDROID OR WIN32)
        set(HANOI_SERVER OFF)
    endif()

    if ( NOT ONLINE_FUNCTIONS)
        set(HANOI_SERVER OFF)
    endif()

endif()

if (NOT DEFINED HANOI_CLIENT)
    set(HANOI_CLIENT ON)

endif()

SET(INSTALLER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/installer/")
SET(DATA_DIR "${INSTALLER_DIR}/packages/HanoiTowers/data")

SET(TARGET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Distro")
SET(PRODUCT_VER_Mj 1)
SET(PRODUCT_VER_Mn 6)
SET(PRODUCT_VER_Re 0)

file(MAKE_DIRECTORY ${TARGET_DIR})
initAll()

addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# Add sub directories

if (HANOI_TESTS)
    set (CREDITS_TESTS ON)
    set (HEART_TESTS ON)
    set (PATRONUM_TESTS ON)

else()
    set (CREDITS_TESTS OFF)
    set (HEART_TESTS OFF)
    set (PATRONUM_TESTS OFF)
endif()

add_subdirectory(submodules/Heart)
add_subdirectory(HanoiTowers/Protockol)

if (HANOI_CLIENT)
    set (CREDITS_EXAMPLES OFF)
    set (LOGINVIEW_EXAMPLES OFF)
    set (VIEWSOLUTIONS_EXAMPLES OFF)

    add_subdirectory(submodules/QMLLoginView)
    add_subdirectory(submodules/SimpleQmlNotify)
    add_subdirectory(submodules/ViewSolutions)
    add_subdirectory(submodules/Credits)

    if (ANDROID)
        set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/HanoiTowers/client/android")
        set(QTAT_APP_PERMISSIONS OFF)
        set(QTAT_APK_EXPANSION_FILES OFF)
        set(QTAT_APK_INFO OFF)
        set(QTAT_SCREEN OFF)
        set(QTAT_SYSTEM OFF)
        set(QTAT_BATTERY_STATE OFF)
        set(QTAT_SIGNAL_STRENGTH OFF)
        set(QTAT_IMAGES OFF)
        set(QTAT_NOTIFICATION OFF)
        set(QTAT_ADMOB_BANNER OFF)
        set(QTAT_ADMOB_INTERSTITIAL ON)
        set(QTAT_ADMOB_REWARDED_VIDEO OFF)
        set(QTAT_PLAY_STORE OFF)
        set(QTAT_GOOGLE_ACCOUNT OFF)
        set(QTAT_GOOGLE_DRIVE OFF)
        set(QTAT_SHARING OFF)
        set(QTAT_USER_MESSAGING_PLATFORM OFF)
        set(QTAT_AUDIO OFF)

        add_subdirectory(submodules/QtAndroidTools/QtAndroidTools)
        include_directories(submodules/QtAndroidTools/QtAndroidTools)

    endif()

    add_subdirectory(HanoiTowers/client)

endif()

if (HANOI_SERVER)
    add_subdirectory(submodules/Patronum)
    add_subdirectory(HanoiTowers/Server)
endif()

