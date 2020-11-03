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
import ".."

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

            CheckBox {
                id: fogConfig
                Component.onCompleted: {
                    checked = backEnd.fog
                }
                text: qsTr("Fog")
                onCheckedChanged: {
                    backEnd.fog = checked;
                }
            }

            CheckBox {
                Component.onCompleted: {
                    checked = backEnd.fogAnimation
                }
                text: qsTr("Fog Animations")
                onCheckedChanged: {
                    backEnd.fogAnimation = checked;
                }
                enabled: fogConfig.checked
            }
        }


        Tower {
            id: exampleTower
            Component.onCompleted: {
                let all = 5
                let value = all
                while (value--) {
                    var temp = Qt.createComponent("../plate.qml")
                    if (temp.status === Component.Ready) {
                        let obj = temp.createObject(this)
                        obj.mass = value + 1
                        obj.value = all
                        exampleTower.push(obj)
                        obj.updateCoordinates();

                    }
                }
            }

            Layout.fillHeight: true
            Layout.fillWidth: true

        }

        anchors.fill: parent

    }

}

