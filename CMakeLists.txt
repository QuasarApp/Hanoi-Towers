#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)
project(MainHanoiTowers)

# Add sub directories
add_subdirectory(SimpleQmlNotify)
add_subdirectory(QtNetworkProtocol)
add_subdirectory(hanoi_towers)
add_subdirectory(HanoiTowersServer)

add_subdirectory(Patronum)

include(QtNetworkProtocol/QuasarAppLib/CMake/QuasarAppCITargets.cmake)
include(QtNetworkProtocol/QuasarAppLib/CMake/ccache.cmake)

SET(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/hanoi_towers/installer/packages/HanoiTowers/data")
SET(BIB_APP "${HanoiTowers_BIN_DIR}/HanoiTowers")
SET(TARGET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Distro")

initRelease()
if (WIN32)
    initDeployQML(${BIB_APP}.exe ${DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    initDeployQIF(${DATA_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/installer" "${CMAKE_CURRENT_SOURCE_DIR}/installer/configWin.xml")

else (WIN32)
    initDeployQML(${BIB_APP} ${DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    initDeployQIF(${DATA_DIR} "${TARGET_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/installer/configLinux.xml")

    initDeploySnap(${TARGET_DIR})
    initReleaseSnap()

endif(WIN32)

initReleaseQif(${DATA_DIR} ${TARGET_DIR})

initDeployAPK("${CMAKE_CURRENT_SOURCE_DIR}/hanoi_towers/android-libHanoiTowers.so-deployment-settings.json" "digitalface" "${SIGN_PATH}/DigitalFaceMobily.keystore" "${SIGN_STORE_PASSWORD}" "${TARGET_DIR}")
