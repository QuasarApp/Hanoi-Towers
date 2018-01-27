import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle{
    property int mass: 0;
    property int value: 1;
    property int pushofnumber: 0
    property int maxHeight:  parent.height * 0.1
    property int curentHeight: parent.height / value * 0.94
    height: (curentHeight < maxHeight )? curentHeight: maxHeight
    width:parent.width * (mass / value) * 0.90
    x:(parent.width - width) / 2 ;
    y:parent.height - (pushofnumber*height * 1.01) - 10.5;
    radius: 10;

    Image {
        id: texture;
        source: "/textures/res/Plate.png"
        anchors.fill: parent;
    }

    BrightnessContrast {
        anchors.fill: texture
        source: texture
        brightness: (value - mass) / value
        contrast: (value - mass) / value
    }

    Behavior on x{
        NumberAnimation
        {
            easing.type: Easing.OutElastic
            duration: 1000
        }
    }
    Behavior on y{
        NumberAnimation
        {
            easing.type: Easing.OutElastic
            duration: 1000
        }
    }
}
