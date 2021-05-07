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

    property var userModel: null
    property bool editable: true

    signal newAvatar(var path);

    Button {
        id: avatarRectangle
        Layout.preferredHeight: eid.height * userDataGrid.rows
        Layout.preferredWidth: Layout.preferredHeight
        Layout.rowSpan: 1
        Image {
            id: userAvatar
            source: "image://HanoiImages/" + ((userModel)? userModel.userId + ":" + userModel.avatarHash: "")
            anchors.fill: parent

            fillMode: Image.PreserveAspectFit

            opacity: 1
        }

        onClicked: {
            if (!editable)
                return;

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
        Layout.fillWidth: true
        rows: (editable && privateRoot.onlineFunctions)? 4 : 3
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
            visible: editable && privateRoot.onlineFunctions

        }

        TextField {
            id: eid
            Layout.preferredWidth: avatarRectangle.width

            readOnly: true
            text: (userModel)? userModel.userId: ""
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: ename
            Layout.preferredWidth: avatarRectangle.width

            readOnly: !editable
            horizontalAlignment: Text.AlignHCenter
            maximumLength: 64
            text: privateRoot.userName
        }

        TextField {
            id: erecord
            Layout.preferredWidth: avatarRectangle.width

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            readOnly: true
            text: (userModel)? userModel.record: ""

        }

        Switch {
            id: eonline
            text: ""
            checked: privateRoot.onlieUser
            visible: !bonline.visible && editable && privateRoot.onlineFunctions
        }

        BusyIndicator {
            id: bonline
            running: true;
            visible: privateRoot.busyVisible

        }
    }

    RowLayout {
        id: rowLayout
        Layout.columnSpan: 2
        visible: editable
        Button {
            id: remove

            Material.background: Material.Red
            text: qsTr("Remove")
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
        property bool onlineFunctions: (userModel)? userModel.onlineFunctions() : false
        property bool busyVisible: (onlineStatus === OnlineStatusQml.loginning ||
                                    onlineStatus === OnlineStatusQml.connecting)
                                    && editable && onlineFunctions

        function accept() {
            if (userModel) {
                userModel.name = ename.text
                if (eonline.checked) {
                    backEnd.onlineRequest(userModel.userId)
                }
                backEnd.updateProfile()

            }
        }

        function restore() {
            ename.text = userName
            eonline.checked = onlieUser
        }

        property int questionCode: 0;
        function remove() {
            questionCode = notificationService.setQuestion(qsTr("Remove %0 user").arg(userModel.userId),
                                            qsTr("All saved data and records will be delete, Do you want continuee?"),
                                            "")
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
