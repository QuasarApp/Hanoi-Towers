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

    BackEnd {
        id: backEnd
    }

    Base.Theme {
        id: theme
    }

    MouseArea {
        id: mouse
    }


    RowLayout{
        height:  gameWindow.height * 0.1
        Item {
            id: mouseContener
            property var mouseObj: null
            width: parent.width * 0.13
            height: parent.height

            function clear() {
                if (mouseObj) {
                    mouseObj.destroy()
                }
            }
            function push(obj) {
                mouseObj = obj
                obj.parent = this
                return true
            }
            function top() {
                return mouseObj
            }
            function pop() {
                mouseObj = null
            }
        }

        Base.BaseText {
            font.bold: true
            font.pointSize: height / text.length * 2
            horizontalAlignment: Text.AlignHCenter
            styleColor: "#973c3c"
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Tower height:")
        }

        Base.BaseButton {
            id: frame

            text: qsTr("lvl ") + (tumbler.spin.currentIndex + 1)
            width: parent.width / 2.2
            height: parent.height

            onClicked: {
                tumbler.visible = true;
            }

        }

        Rectangle {
            id: step
            property int ste: 0
            width: parent.width *0.05
            height: mouseContener.height
            Text {
                font.bold: true
                font.pointSize: 14
                horizontalAlignment: Text.AlignHCenter
                styleColor: "#973c3c"
                verticalAlignment: Text.AlignVCenter
                text: qsTr("step ") + step.ste
                anchors.fill: parent
            }
        }



        Base.BaseButton {
            id: b_exit
            text: qsTr("Return to main menu")

            onClicked: {
                gameWindow.parent.source = "menu/MainMenu.qml"
            }
        }

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
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
        mouseContener.clear()
        while (value--) {
            var temp = Qt.createComponent("plate.qml")
            if (temp.status === Component.Ready) {
                var obj = temp.createObject(parent)
                obj.mass = value + 1
                obj.value = all
                tower1.push(obj)
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
        if (mouseContener.mouseObj) {
            if (obj.push(mouseContener.top())) {
                if(oldTower !== obj) step.ste++
                mouseContener.pop()
            }
        } else {
            if (mouseContener.push((obj.top()))){
                oldTower = obj;
                obj.pop()
            }
        }
        if (tower2.items.length === all || tower3.items.length === all) {
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
    }
    

    PopUp {
        id:popUp;
    }
    
    Tower {
        id: tower1
        width: gameWindow.width * 0.33
        height: gameWindow.height * 0.9
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
