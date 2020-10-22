//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.9
import QtQuick.Controls 2.2
import NotifyModule 1.0
import "./base" as Base
import "./menu" as Menu

import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    title: qsTr("Hanoi Towers")

    Base.Theme{
        id: theme;
    }

    header: Menu.ToolBar {
        state: "MainMenu"
    }

    contentData: Loader {
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
