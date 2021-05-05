//#
//# Copyright (C) 2021 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3

Item {
    id : root

    property string imageSrc: ""
    property string text: ""
    signal click();

    ColumnLayout {


        spacing: 15

        Image {
            id: example

            fillMode: Image.PreserveAspectFit

            Layout.fillWidth: true;
            Layout.fillHeight: true;

            source: root.imageSrc
        }

        Label {
            id: textContainer

            Layout.minimumHeight: 20
            Layout.fillWidth: true;

            wrapMode: Text.WordWrap;

            text: root.text
            font.capitalization: Font.AllUppercase
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        anchors.fill: parent
    }

    MouseArea {
        onClicked:  {
            parent.click();
        }
        anchors.fill: parent
    }
}

