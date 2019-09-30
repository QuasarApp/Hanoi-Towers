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

        property bool isLoad: false

        function start() {
            isLoad = false;
            source = "../game.qml"
        }

        function load() {
            isLoad = true;
            source = "../game.qml"
        }

        onLoaded: {
            item.launch(-1);
            if (isLoad) {
                item.continue_game();
            }
        }
    }
}
