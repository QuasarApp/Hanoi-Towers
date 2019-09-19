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
            source = "../game.qml"
        }

        function load() {
            source = "../game.qml"
            item.continue_game();

        }

        onLoaded: {
            item.launch(-1);
        }
    }
}
