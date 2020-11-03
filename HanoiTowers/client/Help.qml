//#
//# Copyright (C) 2018 - 2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Extras 1.4

import "./base" as Base

Dialog {

    id: helpDialog

    height: parent.height * 0.9
    width: parent.width * 0.9
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2


    Item {

        Image {
            id: example

            height: parent.height * 0.45
            fillMode: Image.PreserveAspectFit
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            source: "/img/Help"
        }

        Base.BaseText {
            id: textContainer

            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05

            anchors.right: parent.right
            anchors.rightMargin: parent.height * 0.05

            anchors.top: example.bottom
            anchors.topMargin: parent.width * 0.05

            anchors.bottom: status.top
            anchors.bottomMargin: parent.height * 0.05


            wrapMode:Text.Wrap ;

            text: qsTr("Your task is to transfer discs of different sizes" +
 "from the left tower to third tower." +
 "You can only transfer the top drive of the tower." +
 "You can not transfer several disks at once and put larger disks on small disks.");

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        Item{
            id: status;
            Base.BaseText{
                id: text
                text: qsTr("Do not show again:");
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.left: parent.left
                anchors.top: parent.top


            }

            StatusIndicator{
                id: indicator
                width: height * 0.9
                color: "#3bffd1"
                active: (backEnd)? !backEnd.isFirst(): false;
                anchors.left: text.right
                anchors.leftMargin: width / 2
                anchors.top: parent.top

                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        backEnd.setShowHelp(indicator.active);
                    }
                }

            }

            Base.BaseButton{
                text: qsTr("Ok");
                onClicked: {
                    backEnd.setShowHelp(!indicator.active);
                    helpDialog.close();
                }
                anchors.top: parent.top
                anchors.right: parent.right
            }

            height: parent.height * 0.1;

            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05

            anchors.right: parent.right
            anchors.rightMargin: parent.height * 0.05

            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.05

        }

        anchors.fill: parent
    }
    onAccepted:{
        backEnd.setShowHelp(!indicator.active);
    }

}
