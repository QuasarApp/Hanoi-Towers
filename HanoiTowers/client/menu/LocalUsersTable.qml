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
import LoginViewModule 1.0
import QtQuick.Window 2.15

Item {
    id:menuPage

    GridLayout {
        id: gridLayout

        rows: 2
        columns: 2

        anchors.fill: parent


        UserView {
            userModel: (backEnd)? backEnd.profileObject: null

            onNewAvatar: {
                backEnd.setNewAvatar(path);
            }
        }

        UsersTable {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rowSpan: 2
            model: (backEnd)? backEnd.profileList: null

            onUserSelected: {
                backEnd.setProfile(userId);
            }

            onCreateNewUser: {
                if (backEnd) {
                    loginPopUp.lognViewModel = createUser;
                    loginPopUp.open()
                }
            }

            state: "Local"
        }

    }

    LoginViewDialog {

        id: loginPopUp
        lognViewModel: userLogin // exampleLogin - this is inited model in main.cpp
        width: 7 * controlPtMaterial
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
