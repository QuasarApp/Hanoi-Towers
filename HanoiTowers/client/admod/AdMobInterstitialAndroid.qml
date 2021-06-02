import QtQuick 2.15
import QtAndroidTools 1.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

QtAndroidAdMobInterstitial {
    id: interstitial

    unitId: "ca-app-pub-5799112356811682/5211864198"
    nonPersonalizedAds: false
    onLoading: {
        loadDialog.open();
    }

    onLoaded: {
        show()
        loadDialog.close();
    }

    onLoadError: {
        loadDialog.close();
    }


    Dialog {
        id: loadDialog
        x: (gameWindow.width - width) / 2
        y: (gameWindow.height - height) / 2

        width: gameWindow.width  * 0.9
        height: gameWindow.height  * 0.9

        header: Label {
            id: title
            text: qsTr("Load ads")
            font.capitalization: Font.AllUppercase
            font.bold: true

            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignTop
        }

        contentItem: ColumnLayout {
            BusyIndicator {
                Layout.fillWidth: true
                running: true
            }

            Label {
                id: textContainer
                Layout.fillWidth: true
                Layout.fillHeight: true

                anchors.fill: parent
                text: qsTr("Sorry, but we need to show you an ad. We want to eat too 😇");

                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignTop
            }
        }

        closePolicy: Popup.NoAutoClose
    }
}


