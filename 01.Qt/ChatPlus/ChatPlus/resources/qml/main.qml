import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    width: 400
    height: 700
    visible: true
    title: qsTr("Chat") + "+"

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: ContactPage {}
    }
}
