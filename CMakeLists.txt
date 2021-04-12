#
# Copyright (C) 2018-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)
project(HanoiTowers)

set(BUILD_SHARED_LIBS ON)



include(submodules/Heart/QuasarAppLib/CMake/ccache.cmake)
include(submodules/Heart/QuasarAppLib/CMake/QuasarAppCITargets.cmake)
include(submodules/Heart/QuasarAppLib/CMake/ProjectOut.cmake)
include(submodules/Heart/QuasarAppLib/CMake/Version.cmake)
include(submodules/Heart/QuasarAppLib/CMake/QtUtils.cmake)

if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
    if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
        initAll()
        return()
    endif()
endif()

if (NOT DEFINED HANOI_TESTS)
    set(HANOI_TESTS ON)

    if (ANDROID)
        set(HANOI_TESTS OFF)
    endif()
endif()

if (NOT DEFINED HANOI_SERVER)
    set(HANOI_SERVER ON)

    if (ANDROID OR WIN32)
        set(HANOI_SERVER OFF)
    endif()

endif()

if (NOT DEFINED HANOI_CLIENT)
    set(HANOI_CLIENT ON)

endif()

SET(INSTALLER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/installer/")
SET(DATA_DIR "${INSTALLER_DIR}/packages/HanoiTowers/data")

SET(BIB_APP "${CMAKE_CURRENT_SOURCE_DIR}/hanoi_towers/build/Release/HanoiTowers")
SET(TARGET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Distro")
SET(PRODUCT_VER_Mj 1)
SET(PRODUCT_VER_Mn 6)
SET(PRODUCT_VER_Re 0)

file(MAKE_DIRECTORY ${TARGET_DIR})

initAll()
addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)

addDeployFromCustomFile("Client" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/Client.json")
addDeployFromCustomFile("Server" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/Server.json")

#if (WIN32)
#    addDeployQIF("Client" ${INSTALLER_DIR} ${TARGET_DIR} "${INSTALLER_DIR}/config/configWin.xml")

#else (WIN32)
#    addDeployQIF("Client" ${INSTALLER_DIR} ${TARGET_DIR} "${INSTALLER_DIR}/config/configLinux.xml")

    #addDeploySnap("Client" ${TARGET_DIR})
    #addReleaseSnap("Client")

#endif(WIN32)

#addReleaseQif("Client" ${DATA_DIR} ${TARGET_DIR})

#addDeployAPK("Android" "${CMAKE_CURRENT_SOURCE_DIR}/hanoi_towers/android-libHanoiTowers.so-deployment-settings.json" "digitalface" "${SIGN_PATH}/DigitalFaceMobily.keystore" "${SIGN_STORE_PASSWORD}" "${TARGET_DIR}")

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
    add_subdirectory(HanoiTowers/client)
endif()

if (HANOI_SERVER)
    add_subdirectory(submodules/Patronum)
    add_subdirectory(HanoiTowers/Server)
    add_subdirectory(HanoiTowers/Terminal)
endif()




