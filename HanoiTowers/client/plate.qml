//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtGraphicalEffects 1.15

Rectangle {
    property int mass: 0;
    property int value: 1;
    property int pushofnumber: 0
    property int maxHeight: (parent)?  parent.height * 0.1 : 0
    property int curentHeight: (parent)? parent.height / value * 0.94 : 0
    height: (parent)? ((curentHeight < maxHeight )? curentHeight: maxHeight): 0
    width: (parent)? parent.width * (mass / value) * 0.90 : 0

    onWidthChanged: {
        updateCoordinates()
    }

    onHeightChanged: {
        updateCoordinates()
    }

    property int durationAnimation: 1000;

    clip: false
    color: "#004bb870"

    function updateCoordinates() {
        x = (parent.width - width) / 2 ;
        y = parent.height - (pushofnumber*height * 1.01) - 10.5;
    }

    Rectangle {
        id: texture
        anchors.fill: parent;
        color: "#4bb870"
        radius: 4;
        clip: true
        Image {
            id: mask;
            fillMode: Image.PreserveAspectCrop
            source: "/textures/res/fog.png"
//            sourceSize: Qt.size(parent.width, parent.height)
            visible: true
            opacity: 0.2
            anchors.fill: parent;

        }
    }


    BrightnessContrast {
        anchors.fill: texture
        source: texture
        brightness: (value - mass) / value
        contrast: (value - mass) / value
        visible:  backEnd && !backEnd.randomColor;

    }

    Colorize {
        anchors.fill: texture
        source:  texture
        hue: (value - mass) / value

        visible: backEnd && backEnd.randomColor;

        saturation: 0.8
        lightness: 0.5
    }

    Behavior on x {
        NumberAnimation
        {
            easing.type: (backEnd && backEnd.animation)? Easing.OutBounce : Easing.OutExpo
            duration: durationAnimation
        }
    }
    Behavior on y {
        NumberAnimation
        {
            easing.type: (backEnd && backEnd.animation)? Easing.OutBounce : Easing.OutExpo
            duration: durationAnimation
        }
    }
}
