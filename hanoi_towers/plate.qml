import QtQuick 2.9
import QtGraphicalEffects 1.0

Rectangle{
    property int mass: 0;
    property int value: 1;
    property int pushofnumber: 0
    property int maxHeight:  parent.height * 0.1
    property int curentHeight: parent.height / value * 0.94
    height: (curentHeight < maxHeight )? curentHeight: maxHeight
    width:parent.width * (mass / value) * 0.90

    property int durationAnimation: 1000;

    radius: 10;

    function updateCoordinates() {
        x = (parent.width - width) / 2 ;
        y = parent.height - (pushofnumber*height * 1.01) - 10.5;
    }

    Image {
        id: texture;
        source: "/textures/res/Plate.png"
        anchors.fill: parent;
    }

    BrightnessContrast {
        anchors.fill: (backEnd.randomColor)? "": texture
        source: (backEnd.randomColor)? "": texture
        brightness: (value - mass) / value
        contrast: (value - mass) / value
    }

    Colorize {
        anchors.fill: (!backEnd.randomColor)? "": texture
        source: (!backEnd.randomColor)? "": texture
        hue: (value - mass) / value

        saturation: 0.8
        lightness: 0.5
    }

    Behavior on x{
        NumberAnimation
        {
            easing.type: (backEnd.animation)? Easing.OutBounce : Easing.OutExpo
            duration: durationAnimation
        }
    }
    Behavior on y{
        NumberAnimation
        {
            easing.type: (backEnd.animation)? Easing.OutBounce : Easing.OutExpo
            duration: durationAnimation
        }
    }
}
