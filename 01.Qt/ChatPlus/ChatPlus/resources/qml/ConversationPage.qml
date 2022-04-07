import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import com.crazyatom.chatplus

Page {
    id: root

    property string inConversationWith
    property string recipientAvatar

    header: ChatToolbar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: inConversationWith
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            spacing: 12
            cacheBuffer: 2
            model: SqlConversationModel { recipient: inConversationWith }
            delegate: Column {
                readonly property bool sentByMe: model.recipient !== "Me"

                anchors.right: sentByMe ? listView.contentItem.right : undefined

                Row {
                    id: messageRow
                    spacing: 6

                    Image {
                        id: avatar
                        width: 40; height: 40
                        anchors.bottom: messageBox.bottom
                        fillMode: Image.PreserveAspectFit
                        source: !sentByMe ? recipientAvatar : ""
                    }

                    Rectangle {
                        id: messageBox
                        width: Math.min(messageText.implicitWidth + 24 + timestampText.implicitWidth, listView.width - (!sentByMe ? avatar.width + messageRow.spacing : 0))
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"
                        radius: 6

                        Label {
                            id: messageText
                            text: model.message
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

                Label {
                    id: timestampText
                    text: Qt.formatDateTime(model.timestamp, "d MMM hh:mm")
                    color: "lightgrey"
                    font { pointSize: 13; bold: true }
                    anchors.right: parent.right
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true

            RowLayout {
                width: parent.width

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: messageField.length > 0
                    onClicked: {
                        listView.model.sendMessage(inConversationWith, messageField.text);
                        messageField.text = "";
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
