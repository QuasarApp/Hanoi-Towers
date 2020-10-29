import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import "./../base" as Base

Rectangle {
    id: root

    color: getStatusColor(onlineStatus)

    property var client: backEnd.onlineStatus;
    property int onlineStatus: (client)? client.status : 0
    property bool returnButton: false
    property bool profileLabel: false

    function getStatusColor(status) {
        switch(status) {

        case 0: return theme.headerColorOffline;
        case 1: return theme.headerColorOnline;
        case 2: return theme.headerColorLogined;
        }
    }

    height: parent.height * 0.15;
    RowLayout {

        Base.BaseText {
            Layout.alignment: Qt.AlignCenter

            text: qsTr("Welcom to Hanoi Towers ") +  backEnd.profile;
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: theme.headerSize;

            visible: !profileLabel
        }

        Base.BaseText {
            Layout.alignment: Qt.AlignCenter

            text: qsTr("Profiles") + " (" + backEnd.profile + ")";
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: theme.headerSize;
            visible: profileLabel

        }

        Base.BaseButton {
            text: qsTr("Return to main menu");
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: theme.pading
            visible: returnButton

            onClicked: {
                menuPage.parent.source = "MainMenu.qml"
            }
        }

        anchors.fill: parent
    }

    states: [
        State {
            name: "MainMenu"
            PropertyChanges {
                target: root
                returnButton: false
                profileLabel: false
                visible: true

            }
        },
        State {
            name: "UsersTable"
            PropertyChanges {
                target: root
                returnButton: true
                profileLabel: true
                visible: true

            }
        },

        State {
            name: "Settings"
            PropertyChanges {
                target: root
                returnButton: true
                profileLabel: false
                visible: true

            }
        },

        State {
            name: "About"
            PropertyChanges {
                target: root
                returnButton: true
                profileLabel: false
                visible: true

            }
        },

        State {
            name: "Game"
            PropertyChanges {
                target: root
                returnButton: true
                profileLabel: false
                visible: false

            }
        }
    ]
}
