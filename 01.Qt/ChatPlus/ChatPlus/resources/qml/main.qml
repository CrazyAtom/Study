import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    id: mainWindow
    width: 400
    height: 700
    visible: true
    title: qsTr("Chat") + "+"

    readonly property int responsiveWidth: 500
    readonly property bool splitState: mainWindow.width > responsiveWidth

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "qrc:/resources/qml/SingleView.qml"

        states: [
            State {
                when: splitState
                PropertyChanges { target: pageLoader; source: "qrc:/resources/qml/SplitView.qml" }
            }
        ]
    }
}
