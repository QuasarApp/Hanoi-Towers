import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13

RowLayout {

    property string name: ""
    property bool online: false
    property string record: "0"
    property int recordLength: 0

    Switch {
        text: qsTr("Online user")
        position: online
    }

    TextField {
        Layout.fillWidth: true
        text: name
    }

    Text {
        text: record
        Layout.minimumWidth: recordLength

    }
}
