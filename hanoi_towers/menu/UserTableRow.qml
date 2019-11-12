import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import "./../base" as Base

Item {
    property string name: ""
    property bool online: false
    property string record: "0"
    property int recordLength: 0

    RowLayout {
        anchors.fill: parent

        Base.Theme{
            id: theme;
        }

        Switch {
            text: qsTr("Online user")
            position: online
        }

        TextField {
            Layout.fillWidth: true
            readOnly: true;
            text: name
        }

        Text {
            text: record
            Layout.minimumWidth: recordLength - deleteUser.width

        }

        Base.BaseButton {
            id: deleteUser;
            text: "X"

            Layout.maximumHeight:  theme.smallbuttonsSize
            Layout.maximumWidth: theme.smallbuttonsSize
        }
    }
}


