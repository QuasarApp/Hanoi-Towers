import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    title: qsTr("Hanoi Towers")

    Loader {
        id: core
        source: "menu/MainMenu.qml"
        anchors.fill: parent

        function start() {
        }

        function load() {
        }

        onLoaded: {
            item.launch(-1);
        }
    }
}
