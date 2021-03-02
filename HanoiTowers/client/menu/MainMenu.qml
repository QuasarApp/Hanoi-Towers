//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "./../base" as Base

Page {
    id:menuPage

    Base.Theme{
        id: theme;
    }

    background: Item {}

    property int onlineStatus: 0;

    signal load()
    signal start()
    signal newState(var state)

    contentItem: Item {
        id: content;

        GridLayout {
            columns: 3
            rows: 9
            flow: GridLayout.TopToBottom
            layoutDirection: Qt.LeftToRight

            Item {
                Layout.rowSpan: 9
                Layout.fillWidth: true
                Layout.minimumWidth: menuPage.width * 0.3
            }

            Item {
                Layout.fillHeight: true
            }

            Base.BaseButton {
                id: load;
                Layout.alignment: Qt.AlignCenter

                text: qsTr("continue");
                Layout.fillWidth: true
                onClicked: {
                    menuPage.load();
                }
            }

            Base.BaseButton {
                id: start;
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true

                text: qsTr("start");
                onClicked: {
                    menuPage.start();
                }
            }

            Base.BaseButton {
                id: world;
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true

                text: qsTr("HanoiTowers World");
                onClicked: {
                    newState("WorldTable")
                }

                visible: onlineStatus === OnlineStatusQml.loggined;
            }

            Base.BaseButton {
                id: about;
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true

                text: qsTr("About");
                onClicked: {
                    newState("About")
                }
            }

            Base.BaseButton {
                id: config;
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true

                text: qsTr("Config");
                onClicked: {
                    newState("Settings")

                }
            }

            Base.BaseButton {
                id: users;
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true

                text: qsTr("Users");
                onClicked: {
                    newState("UsersTable")
                }
            }

            Base.BaseButton {
                id: exit;
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true

                text: qsTr("exit");
                onClicked: {
                    Qt.quit();
                }
            }

            Item {
                Layout.fillHeight: true
            }

            Item {
                Layout.rowSpan: 9
                Layout.fillWidth: true
                Layout.minimumWidth: menuPage.width * 0.3

            }

            anchors.fill: parent

        }
    }


}

