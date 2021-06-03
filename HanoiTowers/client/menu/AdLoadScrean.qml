import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: loadDialog
    x: (gameWindow.width / 2 - width / 2)
    y: (gameWindow.height / 2 - height / 2)

    width: gameWindow.width  * 0.5
    height: gameWindow.height  * 0.5
    modal : true

    background: Rectangle {
        id: background
        property int colorIndex: 0
        property var colors: ["#ffffff",
                              "#00aaff",
                              "#00ffaa",
                              "#ffaa00"]
        color: colors[colorIndex % colors.length]

        Behavior on color {

            ColorAnimation {
                duration: timer.interval
            }
        }

        Component.onCompleted: {
            timer.start()
            colorIndex ++

        }
        Timer {
            id: timer
            interval: 5000
            repeat: true
            running: false
            onTriggered: {
                parent.colorIndex++
            }
        }
    }

    ColumnLayout {
        ProgressBar {
            Layout.fillWidth: true

            indeterminate: true
        }

        Label {
            id: textContainer
            Layout.fillWidth: true

            text: qsTr("Loading ...");
            font.bold: true
            font.pointSize: loadDialog.height * 0.06

            verticalAlignment: Qt.AlignTop
            horizontalAlignment: Qt.AlignHCenter

        }
        anchors.fill: parent
    }

    closePolicy: Popup.NoAutoClose
}
