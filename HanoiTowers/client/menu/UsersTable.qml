//#
//# Copyright (C) 2018 - 2020 QuasarApp.
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

    GridLayout {
        id: gridLayout

        rows: 4
        columns: 3

        anchors.fill: parent

        flow: GridLayout.TopToBottom

        UserView {
            Layout.rowSpan: 2
            userModel: (backEnd)? backEnd.profileObject: null

            onNewAvatar: {
                backEnd.setNewAvatar(path);
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.rowSpan: 2
        }

        TextField {
            readOnly: true;
            text: qsTr("Locale users list")
            Layout.columnSpan: 1
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
            model: (backEnd)? backEnd.profileList: null
            delegate:
                UserTableRow {
                name: username
                points: record
                width: listView.width

                onClicked: {
                    backEnd.setProfile(userid);
                }

            }
        }
        Base.BaseButton {
            id: button
            text: qsTr("Create the new user")
            Layout.alignment: Qt.AlignHCenter| Qt.AlignVCenter
            Layout.columnSpan: 1
            Material.background: Material.Green

            onClicked: {
                if (backEnd) {
                    loginPopUp.lognViewModel = createUser;
                    loginPopUp.open()
                }
            }
        }
    }

    LoginViewDialog {

        id: loginPopUp
        lognViewModel: userLogin // exampleLogin - this is inited model in main.cpp

        Connections {
            target: backEnd;
            function onShowOnlinePage () {
                loginPopUp.lognViewModel = userLogin;
                loginPopUp.open();
            }
        }
    }

    Item {
        id: item1
        x: 80
        y: 349
        width: 200
        height: 200
    }
}
