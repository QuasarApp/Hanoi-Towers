import QtQuick 2.15
import QtAndroidTools 1.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

QtAndroidAdMobInterstitial {
    id: interstitial
    unitId: "ca-app-pub-5799112356811682/5211864198"
    nonPersonalizedAds: false

    onClosed: {
        load()
    }

    onClicked: {
        load()
    }

    Component.onCompleted:  {
        load()
    }

    onLoadError: {
        timer.start()
    }

    Timer {
        id: timer
        interval: 1000
        repeat: false
        onTriggered: {
            interstitial.load()
        }
    }
}
