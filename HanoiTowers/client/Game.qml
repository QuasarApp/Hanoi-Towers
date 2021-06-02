//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

Item {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    property int all: 1
    property var oldTower
    property var upPlate : null

    property var stateWidget: null
    property var stateData: (backEnd)? backEnd.gameState : null

    signal returnToMenu();

    function continue_game() {
        load("Player");
    }

    function launch() {
        if (backEnd.isFirst()) {
            help.open();
        }

        stateData.load();

        start(-1);
    }

    function clear() {
        tower1.clear()
        tower2.clear()
        tower3.clear()

        if (upPlate) {
            upPlate.destroy();
            upPlate = null;
        }
    }

    function load () {

        showAdMobBanner()


        stateData.load();
        stateWidget.tumbler.spin.maximumValue = stateData.lvl;
        stateWidget.tumbler.spin.value = stateData.getMaxValueOfLoadedSaves();

        clear();

        stateWidget.step = stateData.getStep();
        stateWidget.tumbler.spin.value = all = stateData.getMaxValueOfLoadedSaves();

        const towers = [tower1, tower2, tower3]

        for (let i = 0; i < 3; ++i) {
            const toewer = stateData.getTower(i)
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

        stateWidget.tumbler.spin.maximumValue = stateData.lvl;
        if (stateWidget.tumbler.spin.maximumValue <= value || value < 0)
            stateWidget.tumbler.spin.value = all = value = stateWidget.tumbler.spin.maximumValue
        else {
            stateWidget.tumbler.spin.value = all = value
        }
        stateWidget.step = 0

        clear()

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

        saveState();
    }

    function saveState() {
        stateData.setStep(stateWidget.step);
        stateData.setTower(tower1.number, tower1.itemsMassArray);
        stateData.setTower(tower2.number, tower2.itemsMassArray);
        stateData.setTower(tower3.number, tower3.itemsMassArray);

//        backEnd.gameState = stateData;
    }

    function move(from, into) {
        if (from[from.lenght - 1] < into[into.lenght - 1]) {
            tower1.push()
        }
    }

    function trigered(obj) {

        clickSound.play()

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

            showResultMessage(all === stateWidget.tumbler.spin.maximumValue, reward)

            backEnd.setReward(reward);
        }


        oldTower = obj;

        if (objectPlate)
            objectPlate.updateCoordinates();

        if (!upPlate) {
            saveState();
        }
    }

    function showResultMessage(newLvl, reward) {
        if (newLvl) {

            popUp.title = qsTr("Congratulations! You have passed the level %0").arg(all)


            popUp.text = (qsTr("You got <b>%0</b> points for this level and unlocked the level <b>%1</b>!") +
                          qsTr("<br><br> Totally <b>%2</b> steps.") +
                          qsTr("<br> The minimum number of steps for this level : <b>%3</b>")).
            arg(reward).arg(all + 1).
            arg(stateWidget.step).
            arg(backEnd.getMinSteps(all));

            popUp.open()

            const action = function () {
                showAdMobBanner()
                stateData.unlockNextLvl();
                start(stateData.lvl)

            }

            popUp.action = action;

        } else {
            popUp.title = qsTr("Congratulations! You have passed the level %0").arg(all)


            popUp.text = (qsTr("You got <b>%0</b> points for this level!") +
                          qsTr("<br><br> Totally <b>%1</b> steps.") +
                          qsTr("<br> The minimum number of steps for this level : <b>%2</b>")).
            arg(reward).
            arg(stateWidget.step).
            arg(backEnd.getMinSteps(all));

            popUp.open()

            const action = function () {
                showAdMobBanner()
                start(++stateWidget.tumbler.spin.value)

            }

            popUp.action = action;
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

    SoundEffect {
        id: clickSound
        source: "qrc:/sound/blockSound"
    }
}
