import QtQuick 2.15
import QtAndroidTools 1.0

QtAndroidAdMobInterstitial {
    id: interstitial
    unitId: "ca-app-pub-5799112356811682/5211864198"
    nonPersonalizedAds: false
    onLoading: interstitialState.text = "Loading"
    onLoaded: interstitialState.text = "Loaded"
    onLoadError: interstitialState.text = "Error " + errorId
}
