import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "./../base" as Base

Item {
    property bool selected: false
    signal removedRow();
    signal onlineRowChanged(var online);
    signal clicked();

    Base.Theme{
        id: theme;
    }


    Rectangle {
        color: (selected)? "#3700f991" : "#0000f991"
        anchors.fill: parent;

        Behavior on color {
            ColorAnimation {
                duration: 500
            }
        }
    }

    Switch {
        text: qsTr("Online user")
        position: online
        onPositionChanged: {
            onlineRowChanged(Boolean(position));
        }

        ToolTip.visible: pressed || hovered
        ToolTip.delay: Qt.styleHints.mousePressAndHoldInterval
        ToolTip.timeout: 10000
        ToolTip.text: qsTr("If this option is enabled, your saves and the record will be saved on the network.")

        visible: online >= 0
    }

    Text {
        text: display

        anchors.fill: parent;

    }

}
