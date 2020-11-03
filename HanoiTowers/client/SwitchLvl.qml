//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import "./base" as Base

Rectangle {
    id: tumbler
    color: "#ffffff"
    border.color: "#d5d4d4"
    visible: false

    signal start(var lvl);
    property alias spin: spin

    Tumbler {

        visibleItemCount : 5;
        id: spin
        model: 99
        property int value: 4
        property int maximumValue: 99

        delegate: Text {

            color: Qt.rgba(0.5,0.5,0.5,1 / (Math.abs(spin.currentIndex - modelData)))
            text: "" + (modelData + 1)
            width: tumbler.width
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: (spin.height / 4) / (Math.abs(spin.currentIndex - modelData) + 1 )

        }

        onValueChanged: {
            currentIndex = value - 1
        }

        onCurrentIndexChanged: {
            value = currentIndex + 1;
        }

        onMaximumValueChanged: {
            model = maximumValue
        }

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        anchors.bottom: parent.bottom
        anchors.bottomMargin: closeTumbler.height + 5


    }

    Base.BaseButton{
        id: closeTumbler
        text: qsTr("Start")
        onClicked: {
            tumbler.visible = false;
            start(spin.value);
        }
        height: width * 0.6

        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }


    width: (height / 4)

}
