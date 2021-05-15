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
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/uk.ts)


prepareQM(${CURRENT_PROJECT} ${CMAKE_CURRENT_SOURCE_DIR} "${LANGS}")

function(addDeploySnapHanoi name targetDir)

    if(TARGET snap${name})
        message("the snap${name} target already created!")
        return()

    endif(TARGET snap${name})

    find_program(SNAPCRAFT_EXE "snapcraft")

    if(NOT EXISTS ${SNAPCRAFT_EXE})
        message("please install the snapcraft before deploy this project! Use: sudo snap install snapcraft --classic")
        return()
    endif(NOT EXISTS ${SNAPCRAFT_EXE})

    ADD_CUSTOM_TARGET(
        snapClear${name}
        COMMAND snapcraft clean ${SNAPCRAFT_MODE}
        COMMENT "clear snap: snapcraft clean ${SNAPCRAFT_MODE}"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}

    )

    ADD_CUSTOM_TARGET(
        snapcraft${name}Try
        COMMAND snapcraft ${SNAPCRAFT_MODE}
        COMMENT "create snap: snapcraft ${SNAPCRAFT_MODE}"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS deploy${name} snapClear${name}
    )

    ADD_CUSTOM_TARGET(snapcraft${name}Permision
        COMMAND chmod -R 777 ${CMAKE_SOURCE_DIR}/prime/bin ${CMAKE_SOURCE_DIR}/prime/${CURRENT_PROJECT}.sh
        COMMENT "chmod -R 777 ${CMAKE_SOURCE_DIR}/prime/bin ${CMAKE_SOURCE_DIR}/prime/${CURRENT_PROJECT}.sh"
        DEPENDS snapcraft${name}Try
    )

    ADD_CUSTOM_TARGET(
        snapcraft${name}
        COMMAND snapcraft ${SNAPCRAFT_MODE}
        COMMENT "create snap: snapcraft ${SNAPCRAFT_MODE}"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS snapcraft${name}Permision
    )

    ADD_CUSTOM_TARGET(
        snapcraftCopy${name}
        COMMAND ${CMAKE_COMMAND} -E copy *.snap ${targetDir}
        COMMENT "copy snap: ${CMAKE_COMMAND} -E copy *.snap ${targetDir}"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS snapcraft${name}

    )

    ADD_CUSTOM_TARGET(
        snap${name}
        COMMENT "deploy snap${name}"
        DEPENDS snapcraftCopy${name}

    )

    add_dependencies(deploy snap${name})


endfunction()

if (ANDROID)
    set(HANOI_EXTRA_LIBS Heart
                         ${PROJECT_NAME}Protockol
                         QuasarApp
                         LoginView
                         Credits
                         QmlNotyfyService)

    find_package(QT NAMES Qt6 Qt5 COMPONENTS AndroidExtras REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AndroidExtras REQUIRED)

    addDeployAPK(${CURRENT_PROJECT} "${CMAKE_CURRENT_LIST_DIR}/android" "digitalface" "${SIGN_PATH}/DigitalFaceMobily.keystore" "${SIGN_STORE_PASSWORD}" "${TARGET_DIR}" "${HANOI_EXTRA_LIBS}")
    target_link_libraries(${CURRENT_PROJECT} PRIVATE QtAndroidTools Qt${QT_VERSION_MAJOR}::AndroidExtras)

    file(GLOB java_files
       "android/src/com/quasarapp/androidtools/*.java"
    )

    add_custom_target(${name}Android
        SOURCES ${java_files}
    )

else()
    # Desctop deploying
    addDeployFromCustomFile("Client" "${CMAKE_SOURCE_DIR}/Deploy/Client.json")

    if (UNIX)
        #addDeployQIF("Client" ${INSTALLER_DIR} ${TARGET_DIR} "${INSTALLER_DIR}/config/configLinux.xml")

        addDeploySnapHanoi("Client" ${TARGET_DIR})

        #addReleaseSnap("Client")

    endif()
endif()

#addReleaseQif("Client" ${DATA_DIR} ${TARGET_DIR})

