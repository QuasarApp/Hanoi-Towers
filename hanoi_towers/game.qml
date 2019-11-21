//#
//# Copyright (C) 2018 - 2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

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
        console.log("continue");

        load("Player");
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

        backEnd.gameState.load();

        start(-1);
    }
    function load () {

        backEnd.gameState.load();
        tumbler.spin.maximumValue = backEnd.gameState.getMaxValueOfLoadedSaves();

        tower1.clear()
        tower2.clear()
        tower3.clear()

        if (upPlate) {
            upPlate.destroy();
            upPlate = null;
        }

        step.ste = backEnd.gameState.getStep();
        tumbler.spin.value = all = backEnd.gameState.getMaxValueOfLoadedSaves();

        const towers = [tower1, tower2, tower3]

        for (let i = 0; i < 3; ++i) {
            const toewer = backEnd.gameState.getTower(i)
            toewer.forEach((mass)=>{
                               var temp = Qt.createComponent("plate.qml")
                               if (temp.status === Component.Ready) {
                                   let obj = temp.createObject(parent)
                                   obj.mass = mass
                                   obj.value = all
                                   towers[i].push(obj)
                                   obj.updateCoordinates();

                               }
                           });
        }
    }

    function start(value) {

        tumbler.spin.maximumValue = backEnd.gameState.getMaxValueOfLoadedSaves();
        if (tumbler.spin.maximumValue <= value || value < 0)
            tumbler.spin.value = all = value = tumbler.spin.maximumValue
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

        saveState(tower1);
        saveState(tower2);
        saveState(tower3);

    }

    function saveState(obj) {
        backEnd.gameState.setStep(step.ste);
        backEnd.gameState.setTower(obj.number, obj.itemsMassArray);
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
            let reward = backEnd.getMinSteps(all) - step.ste + backEnd.getMinSteps(all);

            if (reward < 1) {
                reward = 1;
            }
            if (all === tumbler.spin.maximumValue) {
                backEnd.gameState.unlockNextLvl();

                popUp.text = (qsTr("You have passed the level in %0 steps and unlocked level %1") +
                                   qsTr("\n Minimum steps for this lvl: %2") +
                                   qsTr("\n you reward = %3")).
                arg(step.ste).arg(all + 1).arg(backEnd.getMinSteps(all)).
                arg(reward);

                popUp.open()
                start(backEnd.gameState.getMaxValueOfLoadedSaves())
            } else {
                popUp.text = (qsTr("You have passed the level in %0 steps.\n") +
                             qsTr("Minimum steps for this lvl: %1") +
                             qsTr("\n you reward = %3")).
                arg(step.ste).arg(backEnd.getMinSteps(all)).arg(reward);

                popUp.open()
                start(++tumbler.spin.value)
            }
            backEnd.setReward(reward);
        }


        oldTower = obj;

        if (objectPlate)
            objectPlate.updateCoordinates();

        if (!upPlate) {
            saveState(tower1);
            saveState(tower2);
            saveState(tower3);
        }
    }
    

    PopUp {
        id:popUp;
    }
    
    Tower {
        id: tower1
        number: 0
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
        number: 1
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
        number: 2
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
