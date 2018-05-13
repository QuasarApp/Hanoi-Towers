import QtQuick 2.9
import QtQuick.Controls 2.2
import "./base" as Base


Item {

    Base.Theme{
        id: theme;
    }

    id: ab
    signal exit
    property string type: qsTr("about")
    Rectangle {
        color: theme.backgroundColor
        anchors.fill: parent
    }
    Image {
        x: 0
        y: 0
        width: parent.width
        height: parent.height * 0.2
        fillMode: Image.PreserveAspectFit
        source: "/res/icon.ico"
    }
    Label {
        id: txt
        x: parent.width * 0.1
        y: parent.height * 0.3
        width: parent.width * 0.8
        height: parent.height * 0.6
        color: theme.buttonsTextColor
        font.pixelSize: (ab.width < ab.height) ? ab.width / 25 : ab.height / 25
        font.italic: true
        wrapMode: Text.Wrap
        text: qsTr("Product of QuasarApp
* Developers:
* Programmer: Yankovich N. Andrei.
* This game is distributed under the LGPLv3 license.
* Contact: https://github.com/EndrII
* Copyright (C) 2018 Yankovich N. Andrei.")
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            ab.parent.source = "game.qml"
        }
    }
}
