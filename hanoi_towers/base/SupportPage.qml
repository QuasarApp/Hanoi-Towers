import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.14

Button {
    Theme{
        id: theme;
    }
    id: ok
    text: ""

    property string txt: qsTr("If you like it or our another products then you can support us." +
                              " For supported just click on this banner(button) and subscribe to any patreon plans of you choose.")

    RowLayout {

        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 10

        Label {
            text: txt;


            Layout.fillWidth: true


            font.pixelSize: theme.fontSize
            opacity: enabled ? 1.0 : 0.3
            color: parent.down ? theme.buttonsTextColor : theme.buttonsTextColorPresed
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            wrapMode: Text.WordWrap

        }

        Image {
            id: logo
            Layout.fillHeight: true
            Layout.preferredWidth: height

            fillMode: Image.PreserveAspectFit
            source: "qrc:/logo"

            Colorize {
                anchors.fill: logo
                source: logo
                hue: 0.0
                saturation: 0.0
                lightness: 0.9
            }
        }


    }

}
