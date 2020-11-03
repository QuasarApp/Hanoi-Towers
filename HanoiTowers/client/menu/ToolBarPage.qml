import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import "./../base" as Base

ToolBar {
    id: root

    property var client: (backEnd)? backEnd.onlineStatus: null;
    property int onlineStatus: (client)? client.status : 0
    property bool returnButton: false
    property string wecomMessage: ""

    property string p_profile: (backEnd)? backEnd.profile: ""

    function getStatusColor(status) {
        switch(status) {

        case 0: return theme.headerColorOffline;
        case 1: return theme.headerColorOnline;
        case 2: return theme.headerColorLogined;
        }
    }

    signal returnToMenu();

    background: Rectangle {
        color: getStatusColor(onlineStatus)
    }

    RowLayout {


        Base.BaseText {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: returnBut.height

            text: wecomMessage
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: theme.headerSize;
        }

        ToolButton {
            id: returnBut
            text: qsTr("Return to main menu");
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: theme.pading
            visible: returnButton

            onClicked: {
                returnToMenu()
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
                visible: true
                wecomMessage: qsTr("Welcom to Hanoi Towers ") + p_profile

            }
        },
        State {
            name: "UsersTable"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                wecomMessage: qsTr("Profiles") + " (" + p_profile + ")";

            }
        },

        State {
            name: "Settings"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                wecomMessage: qsTr("This are the main settings")

            }
        },

        State {
            name: "About"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                wecomMessage: qsTr("About Page")

            }
        },

        State {
            name: "Game"
            PropertyChanges {
                target: root
                returnButton: true
                visible: false
                wecomMessage: ""

            }
        }
    ]
}
