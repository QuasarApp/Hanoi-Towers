import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.1

GridLayout {
    id: mainLayout
    rows: 2
    columns: 2
    clip: true

    property var userModel: null

    signal newAvatar(var path);

    Button {
        Layout.preferredHeight: 50 * Screen.pixelDensity
        Layout.preferredWidth: 50 * Screen.pixelDensity
        Layout.rowSpan: 1
        Image {
            id: userAvatar
            source: "image://HanoiImages/" + ((userModel)? userModel.userId: "")
            anchors.fill: parent

            fillMode: Image.PreserveAspectFit

            opacity: 0.1
        }

        onClicked: {
            fileDialog.open()
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Please choose a new Avatar")
        folder: shortcuts.home
        onAccepted: {
            if (fileDialog.fileUrls.length) {
                newAvatar(fileDialog.fileUrls[0])
            }
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
            text: (userModel)? userModel.userId: ""
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: ename

            text: (userModel)? userModel.name: ""
            horizontalAlignment: Text.AlignHCenter
            maximumLength: 64
        }

        TextField {
            id: erecord

            text: (userModel)? userModel.record: ""
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            readOnly: true

        }

        Switch {
            id: eonline
            checked: (userModel)? userModel.onlineUser: false
            text: ""
        }
    }

    RowLayout {
        id: rowLayout
        Layout.columnSpan: 2

        Button {
            id: remove

            Material.background: Material.Red

            text: qsTr("Remove This Profile")

            readonly property int questionCode: Math.random() * 1000
            onClicked: {
                notificationService.setQuestion(qsTr("Remove %0 user").arg(userModel.userId),
                                             qsTr("All saved data and records will be delete, Do you want continuee?"),
                                             "",
                                             questionCode)

            }

            Connections {
                target: notificationService
                function onQuestionCompleted(accepted, code) {
                    if (accepted && code === remove.questionCode) {
                        console.log("User Removed")
                        // Remove
                    }
                }
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            id: restore
            text: qsTr("Restore")
        }

        Button {
            id: accept
            text: qsTr("Accept")
            Material.background: Material.Green

            onClicked: {
                if (userModel) {
                    userModel.onlineUser = eonline.checked
                    userModel.name = ename.text

                    notificationService.setNotify(qsTr("User is updated"), qsTr("User data will be changed."));

                }
            }

        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}
}
##^##*/
