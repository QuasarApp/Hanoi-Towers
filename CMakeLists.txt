#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)
project(HanoiTowers)

include(QtNetworkProtocol/QuasarAppLib/CMake/ccache.cmake)
include(QtNetworkProtocol/QuasarAppLib/CMake/QuasarAppCITargets.cmake)

SET(INSTALLER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/installer/")
SET(DATA_DIR "${INSTALLER_DIR}/packages/HanoiTowers/data")

SET(BIB_APP "${CMAKE_CURRENT_SOURCE_DIR}/hanoi_towers/build/Release/HanoiTowers")
SET(TARGET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Distro")

file(MAKE_DIRECTORY ${TARGET_DIR})

addDeployFromCustomFile("Client" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/Client.json")
addDeployFromCustomFile("Server" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/Server.json")

if (WIN32)
    addDeployQIF("Client" ${INSTALLER_DIR} ${TARGET_DIR} "${INSTALLER_DIR}/config/configWin.xml")

else (WIN32)
    addDeployQIF("Client" ${INSTALLER_DIR} ${TARGET_DIR} "${INSTALLER_DIR}/config/configLinux.xml")

    addDeploySnap("store" ${TARGET_DIR})
    addReleaseSnap("store")

endif(WIN32)

addReleaseQif("Client" ${DATA_DIR} ${TARGET_DIR})

addDeployAPK("Android" "${CMAKE_CURRENT_SOURCE_DIR}/hanoi_towers/android-libHanoiTowers.so-deployment-settings.json" "digitalface" "${SIGN_PATH}/DigitalFaceMobily.keystore" "${SIGN_STORE_PASSWORD}" "${TARGET_DIR}")

initAll()

# Add sub directories
add_subdirectory(SimpleQmlNotify)
add_subdirectory(QtNetworkProtocol)
add_subdirectory(hanoi_towers)
add_subdirectory(Patronum)
add_subdirectory(HanoiTowersServer)
add_subdirectory(HanoiTowersTerminal)


