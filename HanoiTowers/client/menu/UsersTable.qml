//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import "./../base" as Base
import LoginViewModule 1.0
import QtQuick.Window 2.15

Item {
    id:menuPage

    property var model: null

    signal userSelected(var userId)
    signal createNewUser()

    GridLayout {
        id: gridLayout

        rows: 4
        columns: 3

        anchors.fill: parent

        flow: GridLayout.TopToBottom

        TextField {
            id: title
            readOnly: true;
            text: qsTr("Locale users list")
            Layout.columnSpan: (button.visible)? 1 : 2
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter

        }

        ListView {

            id: listView

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            Layout.rowSpan: 3
            clip: true
            ScrollBar.vertical: ScrollBar {}
            model: menuPage.model
            delegate:
                UserTableRow {
                name: username
                points: record
                number: rowNumber + 1

                width: listView.width

                onClicked: {
                    userSelected(userid)
                }

            }
        }
        Base.BaseButton {
            id: button
            text: qsTr("Create the new user")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.columnSpan: 1
            Material.background: Material.Green

            onClicked: {
                createNewUser()
            }
        }
    }

    states: [
        State {
            name: "Local"
            PropertyChanges {
                target: button
                visible: true
            }

            PropertyChanges {
                target: title
                text: qsTr("Locale users list")

            }
        },
        State {
            name: "World"
            PropertyChanges {
                target: button
                visible: false
            }

            PropertyChanges {
                target: title
                text: qsTr("Best users in the world")

            }
        }
    ]
}
