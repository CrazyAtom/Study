import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    id: root
    width: 640
    height: 300
    color: "white"
    visible: true
    title: qsTr("Hello")

    menuBar: MenuBar {
        Menu {
            title: qsTr("Window")

            MenuItem {
                text: qsTr("&StockBook")
                onTriggered: {
                    mainLoader.source = "StockBookView.qml"
                    console.log("onTriggered : StockBook")
                }
            }

            MenuItem {
                text: qsTr("&About")
                onTriggered: {
                    mainLoader.source = "About.qml"
                    console.log("onTriggered : About")
                }
            }
        }
    }

    Loader {
        id: mainLoader
        anchors.fill: parent
        source: "StockBookView.qml"
    }
}


