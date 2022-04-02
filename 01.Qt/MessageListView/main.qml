import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import App 1.0

Window {
    width: 500
    height: 480
    minimumWidth: 500
    minimumHeight: 480
    visible: true
    color: "#282E33"
    title: qsTr("MessageList")

    Provider {
        id: provider
    }

    function isBlank(str) {
        return (!str || /^\s*$/.test(str));
    }

    function addItem() {
        if (!isBlank(txtInputText.text)) {
            provider.addItem(txtInputText.text)
            console.log("addItem: ", txtInputText.text)
            txtInputText.clear()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 5

            Label {
                text: "Count: " + provider.items.length
                color: "#ffffff"
                font.pointSize: 13
                horizontalAlignment: Text.AlignLeft
            }

            Rectangle { Layout.fillWidth: true }

            Button {
                background: Image {
                    fillMode: Image.PreserveAspectFit
                    source: "./resource/delete_normal.svg"
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.source = "./resource/delete_over.svg"
                        onExited: parent.source = "./resource/delete_normal.svg"
                    }
                }
                onClicked: provider.removeItem(0)
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#18191D"

            ListView {
                id: listView
                clip: true
                anchors.fill: parent
                ScrollBar.vertical: ScrollBar { id: listViewScrollbar; policy: ScrollBar.AsNeeded }
                boundsBehavior: Flickable.DragOverBounds
                cacheBuffer: 2

                model: provider.items
                delegate: StringItemDelegate { parentWidth: parent.width; anchors.left: parent.left; anchors.right: parent.right }

                removeDisplaced: Transition { NumberAnimation { properties: "x,y"; duration: 100; easing.type: easing.InCirc } }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 2

            TextInput {
                id: txtInputText
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                Layout.margins: 10
                font.pointSize: 16
                color: "#ffffff"
                Keys.onReturnPressed: addItem()
            }

            Button {
                id: btnSend
                Layout.preferredWidth: 50
//                Layout.preferredHeight: txtInputText.implicitHeight
                background: Image {
                    fillMode: Image.PreserveAspectFit
                    source: "./resource/send_normal.svg"
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.source = "./resource/send_over.svg"
                        onExited: parent.source = "./resource/send_normal.svg"
                    }
                }
                onClicked: addItem()
            }
        }
    }
}
