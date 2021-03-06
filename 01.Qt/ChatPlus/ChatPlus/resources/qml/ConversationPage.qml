import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import com.crazyatom.chatplus

Page {
    id: conversationPage

    Component.onCompleted: {
        console.log("conversationPage - created")
    }

    Component.onDestruction: {
        console.log("conversationPage - destroyed")
    }

    property string inConversationId

    function getAvatar(min, max) {
        min = Math.ceil(min); max = Math.floor(max);
        var idx = Math.floor(Math.random() * (max - min)) + min;
        return "avatar_" + idx;
    }

    function isBlank(str) {
        return (!str || /^\s*$/.test(str));
    }

    header: ChatToolbar {
        height: 40

        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            visible: !splitState
            onClicked: conversationPage.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: inConversationId
            font.pointSize: 15
            anchors.centerIn: parent
        }
    }

    Page {
        anchors.fill: parent
        visible: isBlank(inConversationId);

        Rectangle {
            width: warningMessage.implicitWidth + 24; height: warningMessage.implicitHeight + 24
            anchors.centerIn: parent
            color: "lightgrey"
            radius: 6

            Label {
                id: warningMessage
                anchors.fill: parent
                anchors.margins: 12
                text: qsTr("Selected Conversation")
                color: "black"
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        visible: !isBlank(inConversationId);

        ScrollView {
            id: scrollView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            focus: true
//            ScrollBar.vertical.interactive: true
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            ListView {
                id: listView
                anchors.fill: parent
                anchors.leftMargin: pane.leftPadding + messageField.leftPadding
                anchors.rightMargin: pane.rightPadding + messageField.rightPadding
                displayMarginBeginning: 40
                displayMarginEnd: 40
                spacing: 5
                cacheBuffer: 2
                model: SqlConversationModel { conversationid: inConversationId }
                delegate: Column {
                    readonly property bool sentByMe: model.author === "-"

                    anchors.right: sentByMe ? listView.contentItem.right : undefined

                    Label {
                        id: authorText
                        text: model.author
                        color: "lightgrey"
                        font.bold: true
                        leftPadding: avatar.width + 10
                        visible: !sentByMe
                    }

                    Row {
                        id: messageRow
                        spacing: 6

                        Image {
                            id: avatar
                            width: 40; height: 40
                            anchors.bottom: messageBox.bottom
                            fillMode: Image.PreserveAspectFit
                            source: !sentByMe ? "qrc:/avatar/" + model.author + ".svg" : ""
                        }

                        Rectangle {
                            id: messageBox
                            width: Math.min(messageText.implicitWidth + 24,
    //                                        listView.width - (!sentByMe ? avatar.width + messageRow.spacing : 0))
                                            listView.width - (avatar.width + messageRow.spacing))
                            height: messageText.implicitHeight + 24
                            color: sentByMe ? "lightgrey" : "steelblue"
                            radius: 6

                            Label {
                                id: messageText
                                anchors.fill: parent
                                anchors.margins: 12
                                text: model.message
                                color: sentByMe ? "black" : "white"
                                wrapMode: Label.Wrap
                            }
                        }
                    }

                    Label {
                        id: timestampText
                        text: Qt.formatDateTime(model.timestamp, "yy.MM.dd  AP h:mm")
                        color: "lightgrey"
                        font { pointSize: 10; bold: true }
                        anchors.right: parent.right
                    }
                }

                property bool scrollEnd: false
//                    onAtYEndChanged: { console.log("onAtYEndChanged = ", atYEnd); scrollEnd = atYEnd }
//                    onContentYChanged: { console.log("onContentYChanged = ", atYEnd); scrollEnd = !atYEnd }
                onCountChanged: {
                    /*if (scrollEnd) */positionViewAtEnd();
                    listView.currentIndex = listView.count - 1
                }

//                ScrollBar.vertical: ScrollBar { }
            }
        }

        Pane {
            id: pane
            padding: 5
            Layout.fillWidth: true

            RowLayout {
                width: parent.width

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                    font.pointSize: 15
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: !isBlank(messageField.text);/*messageField.length > 0*/
                    onClicked: {
                        listView.model.sendMessage(inConversationId, "-", messageField.text);
                        listView.model.sendMessage(inConversationId, getAvatar(1, 11), messageField.text);
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
