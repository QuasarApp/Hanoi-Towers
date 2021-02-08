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
            source: "image://HanoiImages/" + ((userModel)? userModel.avatarHash: "")
            anchors.fill: parent

            fillMode: Image.PreserveAspectFit

            opacity: 1
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

            horizontalAlignment: Text.AlignHCenter
            maximumLength: 64
            text: privateRoot.userName
        }

        TextField {
            id: erecord

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            readOnly: true
            text: (userModel)? userModel.record: ""

        }

        Switch {
            id: eonline
            text: ""
            checked: privateRoot.onlieUser
            visible: privateRoot.onlineStatus === OnlineStatusQml.offline || privateRoot.onlineStatus === OnlineStatusQml.loggined

        }

        BusyIndicator {
            running: true;
            visible: !eonline.visible
        }
    }

    RowLayout {
        id: rowLayout
        Layout.columnSpan: 2

        Button {
            id: remove

            Material.background: Material.Red
            text: qsTr("Remove This Profile")
            onClicked: privateRoot.remove()

        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            id: restore
            text: qsTr("Restore")
            onClicked: privateRoot.restore()

        }

        Button {
            id: accept
            text: qsTr("Accept")
            Material.background: Material.Green

            onClicked: privateRoot.accept()
        }
    }

    Item {
        id: privateRoot

        property string userName: (userModel)? userModel.name: ""
        property bool onlieUser: (userModel)? userModel.onlineUser: false
        property int onlineStatus: (backEnd)? backEnd.onlineStatus : 0

        function accept() {
            if (userModel) {
                userModel.name = ename.text
                notificationService.setNotify(qsTr("User is updated"), qsTr("User data will be changed."));

                if (eonline.checked) {
                    backEnd.onlineRequest(userModel.userId)
                }
            }

            eonline.checked = false

        }

        function restore() {
            ename.text = userName
            eonline.checked = onlieUser
        }

        readonly property int questionCode: Math.random() * 1000
        function remove() {
            notificationService.setQuestion(qsTr("Remove %0 user").arg(userModel.userId),
                                            qsTr("All saved data and records will be delete, Do you want continuee?"),
                                            "",
                                            questionCode)
        }
        Connections {
            target: notificationService
            function onQuestionCompleted(accepted, code) {
                if (accepted && code === privateRoot.questionCode) {
                    if (userModel)
                        backEnd.removeUser(userModel.userId)
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
