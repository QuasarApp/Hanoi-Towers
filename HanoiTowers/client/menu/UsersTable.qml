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

Item {
    id:menuPage

    GridLayout {
        id: gridLayout
        rows: 3
        columns: 3

        anchors.fill: parent

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

        TableView {

            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 3
            clip: true

            model: backEnd.profileList
            delegate: UserTableDelegate {

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

    LoginViewDialog {

        id: loginPopUp
        lognViewModel: userLogin // exampleLogin - this is inited model in main.cpp

        Connections {
            target: backEnd;
            onShowOnlinePage :{
                loginPopUp.open();
            }
        }
    }



}
