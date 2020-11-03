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

    RowLayout {

        ColumnLayout {

            id: colors

            Layout.alignment: Layout.Center

            RadioButton {
                id: r1
                checked: backEnd&& !backEnd.randomColor
                text: qsTr("Standart color")

                onCheckedChanged: {
                    if (backEnd)
                        backEnd.randomColor = false;
                }
            }

            RadioButton {
                id:r2
                checked: backEnd && backEnd.randomColor
                text: qsTr("Random color")
                onCheckedChanged: {
                    backEnd.randomColor = true;
                }
            }

            CheckBox {
                Component.onCompleted: {
                    checked = backEnd.animation
                }
                text: qsTr("Animation")
                onCheckedChanged: {
                    backEnd.animation = checked;
                }
            }
        }

        Image {
            id: colorsView
            fillMode: Image.PreserveAspectFit
            source: (backEnd && backEnd.randomColor)? "../img/random":"../img/standart"

        }

        anchors.fill: parent

    }

}

