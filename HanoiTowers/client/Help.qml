//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Dialog {

    id: helpDialog

    height: parent.height * 0.9
    width: parent.width * 0.9
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2


    ColumnLayout {

        SwipeView {
            id: view

            currentIndex: 0
            function next() {
                view.currentIndex++

                if (view.currentIndex === view.count) {
                    helpDialog.accept()
                }


            }

            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help1.jpg";
                text: qsTr("Tap to select the upper part of tower.")
                onClick: {  view.next() }
            }
            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help2.jpg";
                text: qsTr("Tap to move the selected part to another column.")
                onClick: {  view.next() }

            }
            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help3.jpg";
                text: qsTr("The playing field consists of 3 columns, your task is to move all parts of the tower from the first column to the third.")
                onClick: {  view.next() }

            }
            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help4.jpg";
                text: qsTr("Remember you can't put bigger part on smaller.")
                onClick: {  view.next() }

            }
            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help5.jpg";
                text: qsTr("You will move smaller objects on larger ones in such a way.")
                onClick: {  view.next() }

            }
            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help6.jpg";
                text: qsTr("Try to make as few moves as possible. Good luck!")
                onClick: {  view.next() }

            }
            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help7.jpg";
                text: qsTr("Tap here if you want to change tower high.")
                onClick: {  view.next() }

            }
            HelpPage {
                imageSrc: "qrc:/textures/res/ScreensHelp/Help8.jpg";
                text: qsTr("Tap here if you want to return to main menu.")
                onClick: {  view.next() }

            }

            Layout.fillWidth: true;
            Layout.fillHeight: true;
            Layout.alignment: Qt.AlignHCenter

        }

        PageIndicator {
            id: indicator

            count: view.count
            currentIndex: view.currentIndex
            Layout.alignment: Qt.AlignHCenter

        }

        CheckBox {
            id: check

            Layout.alignment: Qt.AlignBottom
            text: qsTr("Do not show again")
            Component.onCompleted: {
                if (backEnd) {
                    checked = !backEnd.isFirst()
                }
            }

            onCheckedChanged: {
                backEnd.setShowHelp(!check.checked);
            }

        }
        anchors.fill: parent

    }



    standardButtons: Dialog.Ok


}
