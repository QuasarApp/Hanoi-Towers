import QtQuick 2.15

Item {

    property var popup: null

    Component.onCompleted:  {

//        if (!backEnd.isAndroid())
//            return;

//        if (backEnd.isAdMod()) {

//            if (backEnd.launchCount < 6 || backEnd.launchCount % 2 ) {
//                return;
//            }

//            const component = Qt.createComponent("qrc:/menu/Premium.qml");
//            popup = component.createObject(this);
//            popup.open();

//        } else if (backEnd.showCredits) {

//            const component = Qt.createComponent("qrc:/menu/PremiumThanks.qml");
//            popup = component.createObject(this);
//            popup.open();
//        }

//        const component = Qt.createComponent("qrc:/menu/CheatCard.qml");
//        popup = component.createObject(this);
//        popup.open();
    }

    anchors.fill: parent
}
