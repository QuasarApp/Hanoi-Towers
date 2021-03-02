import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import "./../base" as Base

ToolBar {
    id: root

    property int onlineStatus: (backEnd)? backEnd.onlineStatus: 0
    property bool returnButton: false
    property bool gameStateWidget: false

    property string welcomMessage: ""

    property string p_profile: (backEnd)? backEnd.profile: ""

    property alias gameState: gameWidget

    function getStatusColor(status) {
        switch(status) {

        case OnlineStatusQml.connecting: return theme.headerColorOffline;
        case OnlineStatusQml.connected: return theme.headerColorOnline;
        case OnlineStatusQml.loginning: return theme.headerColorOnline;
        case OnlineStatusQml.loggined: return theme.headerColorLogined;
        default:
            return theme.headerColorOffline
        }
    }

    signal returnToMenu();
    signal restart(var level);

    background: Rectangle {
        color: getStatusColor(onlineStatus)
    }

    RowLayout {

        Base.BaseText {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: returnBut.height

            text: welcomMessage
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: theme.headerSize;
        }

        GameStateWidget {
            id: gameWidget
            visible: gameStateWidget
            Layout.preferredHeight: returnBut.height
            Layout.fillWidth: true

            onRestart: {
                root.restart(level);
            }

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
                gameStateWidget: false
                welcomMessage: qsTr("Welcom to Hanoi Towers ") + p_profile

            }
        },
        State {
            name: "UsersTable"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                gameStateWidget: false
                welcomMessage: qsTr("Profiles") + " (" + p_profile + ")";

            }
        },

        State {
            name: "Settings"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                gameStateWidget: false
                welcomMessage: qsTr("This are the main settings")

            }
        },

        State {
            name: "About"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                gameStateWidget: false
                welcomMessage: qsTr("About Page")

            }
        },

        State {
            name: "WorldTable"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                gameStateWidget: false
                welcomMessage: qsTr("World Of Hanoi Towers")

            }
        },

        State {
            name: "Game"
            PropertyChanges {
                target: root
                returnButton: true
                visible: true
                gameStateWidget: true
                welcomMessage: ""

            }
        }
    ]
}
