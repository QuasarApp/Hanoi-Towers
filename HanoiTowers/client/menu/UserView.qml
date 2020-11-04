import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

GridLayout {
    id: mainLayout
    rows: 2
    columns: 2
    clip: true

    Image {
        id: userAvatar
        source: "qrc:/qtquickplugin/images/template_image.png"
        Layout.preferredHeight: 50 * Screen.pixelDensity
        Layout.preferredWidth: 50 * Screen.pixelDensity
        Layout.rowSpan: 1
        fillMode: Image.PreserveAspectFit

        Button {
            anchors.fill: parent
        }
    }

    GridLayout {
        id: userDataGrid
        rows: 4
        columns: 2
        flow: GridLayout.TopToBottom
        Label {
            id: uid
            text: qsTr("Id")
            verticalAlignment: Text.AlignVCenter

        }

        Label {
            id: uname
            text: qsTr("Name")
            verticalAlignment: Text.AlignVCenter

        }

        Label {
            id: urecord
            text: qsTr("Record")
            verticalAlignment: Text.AlignVCenter

        }

        Label {
            id: uonline
            text: qsTr("Online profile")
            verticalAlignment: Text.AlignVCenter

        }

        TextField {
            id: eid

            readOnly: true
            text: ""
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: ename

            text: qsTr("")
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: erecord

            text: "0"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            readOnly: true

        }

        Switch {
            id: eonline
            text: qsTr("")
        }
    }

    RowLayout {
        id: rowLayout
        Layout.columnSpan: 2

        Button {
            id: accept
            text: qsTr("Accept")
        }

        Button {
            id: remove
            text: qsTr("Remove This Profile")
        }
    }

}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}
}
##^##*/
