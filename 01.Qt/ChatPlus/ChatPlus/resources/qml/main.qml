import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    width: 540
    height: 900
    visible: true
    title: qsTr("Chat") + "+"

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: ContactPage {}
    }
}
