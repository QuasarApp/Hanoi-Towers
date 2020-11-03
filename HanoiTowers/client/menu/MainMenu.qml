//#
//# Copyright (C) 2018 - 2020 QuasarApp.
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

    signal load()
    signal start()
    signal newState(var state)

    contentItem: Item {
        id: content;


        ColumnLayout {

            Base.BaseButton {
                id: load;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.15
                Layout.alignment: Qt.AlignCenter

                text: qsTr("continue");
                width:  about.width * 0.8;
                onClicked: {
                    menuPage.load();
                }
            }

            Base.BaseButton {
                id: start;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.15
                Layout.alignment: Qt.AlignCenter

                text: qsTr("start");
                width:  about.width * 0.8;
                onClicked: {
                    menuPage.start();
                }
            }

            Base.BaseButton {
                id: about;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.15
                Layout.alignment: Qt.AlignCenter
                text: qsTr("About");
                width:  config.width * 0.8;
                onClicked: {
                    newState("About")
                }
            }

            Base.BaseButton {
                id: config;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.15
                Layout.alignment: Qt.AlignCenter
                text: qsTr("Config");
                width:  exit.width * 0.8;
                onClicked: {
                    newState("Settings")

                }
            }

            Base.BaseButton {
                id: users;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.15
                Layout.alignment: Qt.AlignCenter
                text: qsTr("Users");
                width:  exit.width * 0.8;
                onClicked: {
                    newState("UsersTable")
                }
            }

            Base.BaseButton {
                id: exit;
                Layout.preferredWidth: parent.width * 0.5;
                Layout.preferredHeight: parent.height * 0.15
                Layout.alignment: Qt.AlignCenter
                width: content.width * 0.5;
                text: qsTr("exit");
                onClicked: {
                    Qt.quit();
                }
            }
            anchors.fill: parent
        }
    }


}

