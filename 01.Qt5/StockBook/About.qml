import QtQuick
import QtQuick.Controls

Rectangle {
    anchors.fill: parent

    Component.onCompleted: {
        console.log("About View - created")
    }

    Component.onDestruction: {
        console.log("About View - destroyed")
    }

    Label {
        anchors.centerIn: parent
        text: "Product Name: Stock Book"
    }
}
