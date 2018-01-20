import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle{
    property int mass: 0;
    property int value: 1;
    property int pushofnumber: 0
    height: parent.height / value * 0.94
    color: "#c0f7de"
    width:parent.width * (mass / value) * 0.90
    x:(parent.width - width) / 2 ;
    y:parent.height - (pushofnumber*height * 1.01) - 10.5;
    radius: 10;

    LinearGradient {
        anchors.fill: parent
        source: parent
        start: Qt.point(0, parent.height / 2)
        end: Qt.point(parent.width, parent.height / 2)
        gradient: Gradient {
            GradientStop {
                position: 0.6
                color:  Qt.rgba(0.160625, 0.576862745, 0.361176471, 1 - ((value - mass) / value))
            }
            GradientStop {
                position: 0.4
                color: Qt.rgba(0.23, 0.751568627, 0.480980392, 1 - ((value - mass) / value))
            }
        }
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
