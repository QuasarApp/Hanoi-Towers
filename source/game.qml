import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import Saver 1.0

Rectangle {
    visible: true
    id: gameWindow
    width: 640
    height: 480
    color: "#ffffff"
    property int all: 1
    MouseArea {
        id: mouse
    }
    Button {
        id: b_start
        text: "Start"
        onClicked: {
            gameWindow.start(spin.value)
        }
        anchors.right: about.left
        anchors.rightMargin: 5;
        width: mouseContener.width
        height: mouseContener.height
    }
    Button {
        id: b_exit
        text: "Exit"
        anchors.right: gameWindow.right
        anchors.rightMargin: 5;
        width: mouseContener.width
        height: mouseContener.height
        onClicked: {
            Qt.quit()
        }
    }
    Button {
        id: about
        text: "About"
        anchors.right: b_exit.left
        anchors.rightMargin: 5;

        width: mouseContener.width
        height: mouseContener.height
        onClicked: {
            gameWindow.parent.source = "about.qml"
        }
    }
    Rectangle {
        id: s_start
        Rectangle {
            Text {
                font.bold: true
                font.pointSize: height / text.length * 2
                horizontalAlignment: Text.AlignHCenter
                styleColor: "#973c3c"
                verticalAlignment: Text.AlignVCenter
                text: "Tower height:"
                anchors.fill: parent
            }
            anchors.left: parent.left
            width: parent.width / 2
            height: parent.height
        }

        Button {
            id: frame

            text: "" + (spin.currentIndex + 1)
            width: parent.width / 2
            height: parent.height

            onClicked: {
                tumbler.visible = true;
            }

            anchors.right: parent.right
            anchors.rightMargin: 5;


        }


        anchors.right: b_start.left
        width: mouseContener.width * 2
        height: mouseContener.height
    }

    Rectangle {
        id: step
        property int ste: 0
        width: mouseContener.width
        height: mouseContener.height
        Text {
            font.bold: true
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
            styleColor: "#973c3c"
            verticalAlignment: Text.AlignVCenter
            text: "" + step.ste
            anchors.fill: parent
        }
        anchors.left: mouseContener.right
    }
    Item {
        id: mouseContener
        property var mouseObj: null
        width: parent.width * 0.14
        height: parent.height * 0.1
        x: mouse.mouseX
        y: mouse.mouseY
        function clear() {
            if (mouseObj) {
                mouseObj.destroy()
            }
        }
        function push(obj) {
            mouseObj = obj
            obj.parent = this
            return true
        }
        function top() {
            return mouseObj
        }
        function pop() {
            mouseObj = null
        }
    }
    function start(value) {
        spin.maximumValue = saver.reed
        if (saver.reed <= value || value < 0)
            spin.value = all = value = saver.reed
        else {
            spin.value = all = value
        }
        step.ste = 0
        tower1.clear()
        tower2.clear()
        tower3.clear()
        mouseContener.clear()
        while (value--) {
            var temp = Qt.createComponent("plate.qml")
            if (temp.status === Component.Ready) {
                var obj = temp.createObject(parent)
                obj.mass = value + 1
                obj.value = all
                tower1.push(obj)
            }
        }
    }
    function move(from, into) {
        if (from[from.lenght - 1] < into[into.lenght - 1]) {
            tower1.push()
        }
    }
    function trigered(obj) {
        if (mouseContener.mouseObj) {
            if (obj.push(mouseContener.top())) {
                step.ste++
                mouseContener.pop()
            }
        } else {
            if (mouseContener.push((obj.top())))
                obj.pop()
        }
        if (tower2.items.length === all || tower3.items.length === all) {
            if (all == spin.maximumValue) {
                saver.save(spin.value = spin.maximumValue = all + 1)
                messageDialog.show("You have passed the level in " + step.ste
                                   + " steps\n and unlocked level " + all + ".")
                start(spin.value)
            } else {
                messageDialog.show(
                            "You have passed the level in " + step.ste + " steps\n.")
                start(++spin.value)
            }
        }
    }
    Saver {
        id: saver
    }
    MessageDialog {
        id: messageDialog
        title: qsTr("You win!!")

        function show(caption) {
            messageDialog.text = caption
            messageDialog.open()
        }
    }
    Tower {
        id: tower1
        width: gameWindow.width * 0.33
        height: gameWindow.height * 0.9
        anchors.left: gameWindow.left
        anchors.bottom: gameWindow.bottom
        onClick: {
            trigered(obj)
        }
    }
    Tower {
        id: tower2
        width: tower1.width
        height: tower1.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: tower1.bottom
        onClick: {
            trigered(obj)
        }
    }
    Tower {
        id: tower3
        width: tower2.width
        height: tower2.height
        anchors.right: gameWindow.right
        anchors.bottom: tower2.bottom
        onClick: {
            trigered(obj)
        }
    }

    Rectangle {
        id: tumbler
        color: "#ffffff"
        border.color: "#d5d4d4"
        visible: false



        Tumbler {

            visibleItemCount : 5;
            id: spin
            model: 99
            property int value: 4
            property int maximumValue: 99

            function format(){

            }

            delegate: Text {

                color: Qt.rgba(0.5,0.5,0.5,1 / (Math.abs(spin.currentIndex - modelData)))
                text: "" + (modelData + 1)

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: (spin.height / 4) / (Math.abs(spin.currentIndex - modelData) + 1 )

            }

            onValueChanged: {
                currentIndex = value - 1
            }

            onCurrentIndexChanged: {
                value = currentIndex + 1;
            }

            onMaximumValueChanged: {
                model = maximumValue
            }
            anchors.fill: parent

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            anchors.bottom: parent.bottom
            anchors.bottomMargin: closeTumbler.height + 5


        }

        Button{
            id: closeTumbler
            text: qsTr("Ok")
            onClicked: {
                tumbler.visible = false;
            }
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
        }


        width: (height / 4)

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.bottomMargin: 20


    }
}
