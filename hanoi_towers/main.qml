import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    id: gameWindow
    width: 1240
    height: 720
    title: qsTr("Hanoi Towers")

    Loader {
        id: core
        source: "menu/MainMenu.qml"
        anchors.fill: parent
        onLoaded: {
            item.launch(-1);
        }
    }
}
