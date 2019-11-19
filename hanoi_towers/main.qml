//#
//# Copyright (C) 2018 - 2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.9
import QtQuick.Controls 2.2
import NotifyModule 1.0

ApplicationWindow {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    title: qsTr("Hanoi Towers")

    Loader {
        id: core
        source: "menu/MainMenu.qml"
        anchors.fill: parent

        property bool isLoad: false

        function start() {
            isLoad = false;
            source = "../game.qml"
        }

        function load() {
            isLoad = true;
            source = "../game.qml"
        }

        onLoaded: {
            if (isLoad) {
                item.continue_game();
            } else {
                item.launch(-1);
            }
        }
    }

    NotificationServiceView {
         anchors.fill: parent;
    }
}
