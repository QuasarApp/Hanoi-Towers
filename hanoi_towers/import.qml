import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1

/*
    QmlImports.qml

    Declaration of QML Imports required by project.

    This is necessary if we want to keep qml files in a folder
    separate from .pro file because  of the way qmlimportscanner works.
    If these imports are not declared, qmake will not recognize them,
    and QtQuick will not be packaged with statically built apps and imported
    at runtime.

    This must be kept in the same directory as your .pro file
*/

QtObject {}
