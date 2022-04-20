import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    id: mainWindow
    width: 400; height: 700
    minimumWidth: 400; minimumHeight: 500
    visible: true
    title: qsTr("Chat") + "+"

    readonly property int responsiveWidth: 600
    readonly property bool splitState: mainWindow.width > responsiveWidth

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "qrc:/qml/SingleView.qml"

        states: [
            State {
                when: splitState
                PropertyChanges { target: pageLoader; source: "qrc:/qml/SplitView.qml" }
            }
        ]
    }
}
