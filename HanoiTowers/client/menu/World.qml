import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: worldTabel

    GridLayout {
        id: gridLayout

        rows: 2
        columns: 1

        anchors.fill: parent

        UserView {
            userModel: (backEnd)? backEnd.bestUser: null
            editable: false;
        }

        UsersTable {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: (backEnd)? backEnd.worldList: null
            state: "World"

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
    }

    Item {
        id: privateRoot

        function showUser(id) {

        }
    }
}
