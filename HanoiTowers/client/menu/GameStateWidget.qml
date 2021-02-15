import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QtQuick.Window 2.1

import "../base" as Base
import ".."

RowLayout {
    id: root

    property alias tumbler: tumblerWidget
    property alias step: stepWidget.ste
    signal restart(var level);

    spacing: Screen.pixelDensity * 5

    Label {
        id: towerheight
        font.bold: true
        font.pixelSize: theme.gameStateFontSize;
        horizontalAlignment: Text.AlignHCenter

        styleColor: "#973c3c"
        verticalAlignment: Text.AlignVCenter
        text: qsTr("Tower height: ")

    }

    Base.BaseButton {
        id: frame

        text: tumblerWidget.spin.currentIndex + 1
        onClicked: {
            tumblerWidget.visible = true;
        }

        SwitchLvl {
            id: tumblerWidget

            onStart: {
                restart(lvl);
            }
            height: parent.height * 4
            anchors.top: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }

    Label {
        id: stepWidget
        property int ste: 0
        font.bold: true

        font.pixelSize: theme.gameStateFontSize;
        horizontalAlignment: Text.AlignHCenter
        styleColor: "#973c3c"
        verticalAlignment: Text.AlignVCenter
        text: qsTr("step ") + step
    }

}
