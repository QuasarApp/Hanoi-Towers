import QtQuick 2.9
import QtQuick.Controls 2.2

Item {

    id: ab
    signal exit
    property string type: "about"
    Rectangle {
        color: Qt.rgba(0.25, 0.25, 0.25, 1)
        anchors.fill: parent
    }
    Image {
        x: 0
        y: 0
        width: parent.width
        height: parent.height * 0.2
        fillMode: Image.PreserveAspectFit
        source: "/icon.png"
    }
    Label {
        id: txt
        x: 0
        y: parent.height * 0.2
        width: parent.width
        height: parent.height * 0.7
        color: "white"
        font.pixelSize: (ab.width < ab.height) ? ab.width / 15 : ab.height / 15
        font.italic: true
        wrapMode: Text.Wrap
        text: "Product of DigitalFace
* Developers:
* Programmer: Yankovich N. Andrei.
* This game is distributed under the LGPLv3 license.
* Contact: https://github.com/EndrII
* Copyright (C) 2017 Yankovich N. Andrei."
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            ab.parent.source = "game.qml"
        }
    }
}
