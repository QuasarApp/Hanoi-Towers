import QtQuick 2.9
import QtQuick.Controls 2.2
import "./base" as Base

Rectangle {
    id: tumbler
    color: "#ffffff"
    border.color: "#d5d4d4"
    visible: false

    signal start(var lvl);
    property var spin: spin

    Tumbler {

        visibleItemCount : 5;
        id: spin
        model: 99
        property int value: 4
        property int maximumValue: 99

        function format(){

        }

        delegate: Text {

            color: Qt.rgba(0.5,0.5,0.5,1 / (Math.abs(spin.currentIndex - modelData)))
            text: "" + (modelData + 1)

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
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }


    width: (height / 4)

}
