//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15

import "./base" as Base


Item {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    property int all: 1
    property var oldTower
    property var upPlate : null

    property var stateWidget: null

    signal returnToMenu();

    function continue_game() {
        load("Player");
    }

    Base.Theme {
        id: theme
    }

    function launch() {
        if (backEnd.isFirst()) {
            help.open();
        }

        backEnd.gameState.load();

        start(-1);
    }
    function load () {

        backEnd.gameState.load();
        stateWidget.tumbler.spin.maximumValue = backEnd.gameState.getMaxValueOfLoadedSaves();

        tower1.clear()
        tower2.clear()
        tower3.clear()

        if (upPlate) {
            upPlate.destroy();
            upPlate = null;
        }

        stateWidget.step = backEnd.gameState.getStep();
        stateWidget.tumbler.spin.value = all = backEnd.gameState.getMaxValueOfLoadedSaves();

        const towers = [tower1, tower2, tower3]

        for (let i = 0; i < 3; ++i) {
            const toewer = backEnd.gameState.getTower(i)
            toewer.forEach((mass)=>{
                               var temp = Qt.createComponent("plate.qml")
                               if (temp.status === Component.Ready) {
                                   let obj = temp.createObject(this)
                                   obj.mass = mass
                                   obj.value = all
                                   towers[i].push(obj)
                                   obj.updateCoordinates();

                               }
                           });
        }
    }

    function start(value = -1 ) {

        stateWidget.tumbler.spin.maximumValue = backEnd.gameState.lvl;
        if (stateWidget.tumbler.spin.maximumValue <= value || value < 0)
            stateWidget.tumbler.spin.value = all = value = stateWidget.tumbler.spin.maximumValue
        else {
            stateWidget.tumbler.spin.value = all = value
        }
        stateWidget.step = 0
        tower1.clear()
        tower2.clear()
        tower3.clear()
        while (value--) {
            var temp = Qt.createComponent("plate.qml")
            if (temp.status === Component.Ready) {
                let obj = temp.createObject(this)
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
        backEnd.gameState.setStep(stateWidget.step);
        backEnd.gameState.setTower(obj.number, obj.itemsMassArray);
    }

    function move(from, into) {
        if (from[from.lenght - 1] < into[into.lenght - 1]) {
            tower1.push()
        }
    }
    function trigered(obj) {

        stateWidget.tumbler.visible = false;
        let objectPlate = null;
        if (upPlate) {
            if (obj.push(upPlate)) {
                if(oldTower !== obj) stateWidget.step++
                objectPlate = upPlate;
                upPlate = null
            }
        } else {
            upPlate = obj.up();

        }


        if ( tower3.items.length === all) {
            let reward = backEnd.getMinSteps(all) - stateWidget.step + backEnd.getMinSteps(all);

            if (reward < 1) {
                reward = 1;
            }
            if (all === stateWidget.tumbler.spin.maximumValue) {

                popUp.text = (qsTr("You have passed the level in %0 steps and unlocked level %1") +
                                   qsTr("\n Minimum steps for this lvl: %2") +
                                   qsTr("\n you reward = %3")).
                arg(stateWidget.step).arg(all + 1).arg(backEnd.getMinSteps(all)).
                arg(reward);

                popUp.open()

                const action = function () {
                    backEnd.gameState.unlockNextLvl();
                    start(backEnd.gameState.lvl)
                }

                popUp.action = action;

            } else {
                popUp.text = (qsTr("You have passed the level in %0 steps.\n") +
                             qsTr("Minimum steps for this lvl: %1") +
                             qsTr("\n you reward = %3")).
                arg(stateWidget.step).arg(backEnd.getMinSteps(all)).arg(reward);

                popUp.open()

                const action = function () {
                    start(++stateWidget.tumbler.spin.value)
                }

                popUp.action = action;
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

    Help {
        id: help
    }

}
