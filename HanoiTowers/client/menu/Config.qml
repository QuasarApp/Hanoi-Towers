//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import "./../base" as Base

Item {
    id:menuPage

    Base.Theme{
        id: theme;
    }

    Row {

        Image {
            id: colorsView
            fillMode: Image.PreserveAspectFit
            source: (backEnd.randomColor)? "../img/random":"../img/standart"
            height: width
            width: menuPage.width * 0.5

        }

        Column {

            id: colors
            width: colorsView.width
            height: colorsView.height
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.1
            anchors.left: colorsView.right


            RadioButton {
                id: r1
                checked: !backEnd.randomColor
                text: qsTr("Standart color")

                width: colorsView.width;
                onCheckedChanged: {
                    backEnd.randomColor = false;
                }
            }

            RadioButton {
                id:r2
                checked: backEnd.randomColor
                text: qsTr("Random color")
                width: colorsView.width;
                onCheckedChanged: {
                    backEnd.randomColor = true;
                }
            }

            CheckBox {
                height: colorsView.height * 0.3;
                width: colorsView.width;
                text: qsTr("Animation")
                checked: backEnd.animation
                onCheckedChanged: {
                    backEnd.animation = checked;
                }
            }

            Layout.alignment: Qt.AlignLeft
        }

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top

    }

}

