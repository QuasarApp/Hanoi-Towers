import QtQuick 2.15

Item {

    property var popup: null

    Component.onCompleted:  {

        if (!(backEnd.isAndroid() && backEnd.isAdMod())) {
            const component = Qt.createComponent("qrc:/menu/Premium.qml");
            popup = component.createObject(this);
            popup.open();

        } else if (backEnd.showCredits) {

            const component = Qt.createComponent("qrc:/menu/PremiumThanks.qml");
            popup = component.createObject(this);
            popup.open();
        }
    }

    anchors.fill: parent
}
