//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import "./base" as Base
import QtQuick.Layouts 1.15
import QuasarAppCreditsModule 1.0

Item {
    Base.Theme{
        id: theme;
    }

    id: ab
    signal exit
    property string type: qsTr("about")
    Rectangle {
        color: theme.backgroundColor
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.fill: parent
        TabBar {
            id: bar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("About")
            }
            TabButton {
                text: qsTr("Credits")
            }
        }


        StackLayout {
            currentIndex: bar.currentIndex
            Layout.fillWidth: true
            Layout.fillHeight: true

            Item {
                id: name
                Image {
                    x: 0
                    y: 0
                    width: parent.width
                    height: parent.height * 0.2
                    fillMode: Image.PreserveAspectFit
                    source: "/res/icon.ico"
                }
                Label {
                    id: txt
                    x: parent.width * 0.1
                    y: parent.height * 0.3
                    width: parent.width * 0.8
                    height: parent.height * 0.6
                    color: theme.buttonsTextColor
                    font.pixelSize: (ab.width < ab.height) ? ab.width / 25 : ab.height / 25
                    font.italic: true
                    wrapMode: Text.Wrap
                    text: qsTr("Product of QuasarApp
            * Developers:
            * Programmer: Yankovich N. Andrei.
            * Disigner: Chernenkov I. Oleg.
            * This game is distributed under the LGPLv3 license.
            * Contact: https://github.com/EndrII
            * Copyright (C) 2018-2019 Yankovich N. Andrei.
            * Copyright (C) 2019-2021 QuasarApp group.")
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        ab.parent.source = "menu/MainMenu.qml"
                    }
                }
            }

            Credits {
                state: "patreon"

            }
        }

    }
}
