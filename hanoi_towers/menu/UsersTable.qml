//#
//# Copyright (C) 2018 - 2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import "./../base" as Base

Item {
    id:menuPage

    Base.Theme{
        id: theme;
    }

    Rectangle {
        id: head
        color: theme.headerColor
        height: parent.height * 0.15;
        RowLayout {

            Base.BaseText {
                Layout.alignment: Qt.AlignCenter

                text: qsTr("Profiles") + " (" + backEnd.profile + ")";
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: theme.headerSize;
            }

            Base.BaseButton {
                text: qsTr("Return to main menu");
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: theme.pading

                onClicked: {
                    menuPage.parent.source = "MainMenu.qml"
                }
            }

            anchors.fill: parent
        }
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

    }

    GridLayout {
        id: gridLayout
        rows: 3
        columns: 3

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: head.bottom


        Switch {
            id: element
            text: qsTr("Online user")
        }

        TextField {
            Layout.fillWidth: true

            id: textField
            text: ""
            placeholderText: qsTr("Enter the name of new user");
        }

        Base.BaseButton {
            id: button
            text: qsTr("Create the new user")

            onClicked: {
                if (backEnd) {
                    backEnd.createProfile(textField.text, element.position)
                }
            }
        }

        ListView {

            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 3
            clip: true

            model: backEnd.profileList
            delegate: UserTableRow {
                name: modelData
                online: backEnd.isOnline(modelData)
                record: backEnd.record(modelData)
                width: listView.width
                recordLength: button.width - gridLayout.rowSpacing
                selected: modelData == backEnd.profile;
                onRemovedRow: {
                    backEnd.removeUser(modelData)
                }

                onOnlineRowChanged: {
                    backEnd.setOnline(modelData, online);
                }

                onClicked: {
                    backEnd.setProfile(modelData);
                }
            }
        }

    }

}
