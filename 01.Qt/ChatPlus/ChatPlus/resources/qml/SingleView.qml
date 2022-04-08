import QtQuick
import QtQuick.Controls

StackView {
    id: stackView
    anchors.fill: parent
    initialItem: ContactPage {}

    Component.onCompleted: {
        console.log("stackView - created")
    }

    Component.onDestruction: {
        console.log("stackView - destroyed")
    }
}

