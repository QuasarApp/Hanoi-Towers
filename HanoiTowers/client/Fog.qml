import QtQuick 2.15

Item {
    id: root
    property string source: ""
    property alias run: tim.running
    property real spread: 0.1
    readonly property int duration: 10000

    visible: backEnd.fog


    Image {
        id: background
        fillMode: Image.PreserveAspectCrop
        source: root.source
        sourceSize: Qt.size(parent.width, parent.height)
        visible: true
        opacity: 1
        height: parent.height
        width: parent.width * (1 + spread)
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutQuart
                duration: root.duration
            }
        }
    }

    Image {
        id: background2
        fillMode: Image.PreserveAspectCrop
        source: root.source
        sourceSize: Qt.size(parent.width, parent.height)
        opacity: 0
        visible: true
        anchors.fill: parent
        height: parent.height
        width: parent.width * (1 + spread)
        x:  height * spread
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutQuart
                duration: root.duration
            }
        }
    }

    Image {
        id: background3
        fillMode: Image.PreserveAspectCrop
        source: root.source
        sourceSize: Qt.size(parent.width, parent.height)
        opacity: 0
        visible: true
        anchors.fill: parent
        height: parent.height
        width: parent.width * (1 + spread)
        x: - (height * spread)

        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutQuart
                duration: root.duration
            }
        }
    }


    Timer {
        id: tim

        repeat: true;
        running: backEnd.fogAnimation
        interval: root.duration
        onTriggered: {

            background.opacity = Math.random()
            background2.opacity = Math.random()
            background3.opacity = Math.random()

        }
    }
}
