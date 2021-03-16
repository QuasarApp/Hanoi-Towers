import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: worldTabel

    GridLayout {
        id: gridLayout

        rows: 2
        columns: 3

        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Text {
                text: "BEST IMG"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        UserView {
            userModel: (backEnd)? backEnd.bestUser: null
            editable: false;
        }

        Item {
            Layout.fillWidth: true
            Text {
                text: "BEST IMG"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
        }

        UsersTable {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: (backEnd)? backEnd.worldList: null
            state: "World"
            Layout.columnSpan: 3

            onUserSelected: {
                privateRoot.showUser(userId);
            }

        }

    }

    Dialog {
        id: preview;
        contentItem: UserView {
            userModel: (backEnd)? backEnd.selectedUser: null
            editable: false;
        }

        standardButtons: Dialog.Close
        x: parent.width / 2 - width / 2;
        y: parent.height / 2 - height / 2;

    }

    Item {
        id: privateRoot

        function showUser(id) {
            if (backEnd)
                backEnd.selectUserFromWorldTable(id);

            preview.open()

        }
    }
}
