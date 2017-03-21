import QtQuick 2.0

Rectangle{
    property int mass: 0;
    property int value: 1;
    property int pushofnumber: 0
    height: parent.height/value*0.94
    color: "#c0f7de"
    width:parent.width*(mass/value)*0.90
    x:(parent.width-width)/2;
    y:parent.height-(pushofnumber*height*1.01)-10.5;
    border.color: "#000000"
    radius: 10;
    function flush(){}
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
