import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import BackEnd 1.0
import "./base" as Base


Rectangle {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    color: "#ffffff"
    property int all: 1
    property var oldTower
    property var upPlate : null

    function continue_game() {

    }

    BackEnd {
        id: backEnd
    }

    Base.Theme {
        id: theme
    }

    MouseArea {
        id: mouse
    }

    Base.BaseText {
        id: towerheight
        font.bold: true
        font.pointSize: height / text.length * 2
        horizontalAlignment: Text.AlignHCenter
        height: parent.height * 0.08

        styleColor: "#973c3c"
        verticalAlignment: Text.AlignVCenter
        text: qsTr("Tower height:")

        anchors.left: parent.left
        anchors.top:  parent.top
        anchors.leftMargin: width * 0.2

    }

    Base.BaseButton {
        id: frame

        text: qsTr("lvl ") + (tumbler.spin.currentIndex + 1)
        width: parent.width * 0.13
        height: parent.height * 0.08

        onClicked: {
            tumbler.visible = true;
        }
        anchors.left: towerheight.right
        anchors.top: parent.top
        anchors.leftMargin: frame.width * 0.2

    }

    Rectangle {
        id: step
        property int ste: 0
        width: frame.width * 0.8
        height: frame.height
        Text {
            font.bold: true
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
            styleColor: "#973c3c"
            verticalAlignment: Text.AlignVCenter
            text: qsTr("step ") + step.ste
            anchors.fill: parent
        }

        anchors.left: frame.right
        anchors.leftMargin: frame.width * 0.2
        anchors.top: parent.top
    }

    Base.BaseButton {
        id: b_exit
        text: qsTr("Return to main menu")
        height: frame.height
        width: frame.width * 2

        onClicked: {
            gameWindow.parent.source = "menu/MainMenu.qml"
        }

        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.05;
        anchors.top: parent.top

    }

    function launch(){
        if (backEnd.isFirst) {
            help.open();
        }
        start(-1);
    }

    function start(value) {

        tumbler.spin.maximumValue = backEnd.reed
        if (backEnd.reed <= value || value < 0)
            tumbler.spin.value = all = value = backEnd.reed
        else {
            tumbler.spin.value = all = value
        }
        step.ste = 0
        tower1.clear()
        tower2.clear()
        tower3.clear()
        while (value--) {
            var temp = Qt.createComponent("plate.qml")
            if (temp.status === Component.Ready) {
                let obj = temp.createObject(parent)
                obj.mass = value + 1
                obj.value = all
                tower1.push(obj)
                obj.updateCoordinates();

            }
        }
    }
    function move(from, into) {
        if (from[from.lenght - 1] < into[into.lenght - 1]) {
            tower1.push()
        }
    }
    function trigered(obj) {
        tumbler.visible = false;
        let objectPlate = null;
        if (upPlate) {
            if (obj.push(upPlate)) {
                if(oldTower !== obj) step.ste++
                objectPlate = upPlate;
                upPlate = null
            }
        } else {
            upPlate = obj.up();

        }
        if ( tower3.items.length === all) {
            if (all == tumbler.spin.maximumValue) {
                backEnd.save(tumbler.spin.value = tumbler.spin.maximumValue = all + 1)
                popUp.text = qsTr("You have passed the level in %0 steps and unlocked level %1" +
                                   "\n Minimum steps for this lvl: %2").
                arg(step.ste).arg(all + 1).arg(backEnd.getMinSteps(all));

                popUp.open()
                start(tumbler.spin.value)
            } else {
                popUp.text = qsTr("You have passed the level in %0 steps.\n" +
                                     "Minimum steps for this lvl: %1").
                arg(step.ste).arg(backEnd.getMinSteps(all));

                popUp.open()
                start(++tumbler.spin.value)
            }
        }

        oldTower = obj;

        if (objectPlate)
            objectPlate.updateCoordinates();
    }
    

    PopUp {
        id:popUp;
    }
    
    Tower {
        id: tower1
        width: gameWindow.width * 0.33
        height: gameWindow.height * 0.75
        anchors.left: gameWindow.left
        anchors.bottom: gameWindow.bottom
        onClick: {
            trigered(obj)
        }
    }
    Tower {
        id: tower2
        width: tower1.width
        height: tower1.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: tower1.bottom
        onClick: {
            trigered(obj)
        }
    }
    Tower {
        id: tower3
        width: tower2.width
        height: tower2.height
        anchors.right: gameWindow.right
        anchors.bottom: tower2.bottom
        onClick: {
            trigered(obj)
        }
    }

    SwitchLvl {
        id: tumbler

        x: frame.x
        y: frame.y + frame.height
        width: frame.width
        height: parent.height * 0.7

        onStart: {
            gameWindow.start(lvl);
        }
    }

    Help{
        id: help
    }

}
