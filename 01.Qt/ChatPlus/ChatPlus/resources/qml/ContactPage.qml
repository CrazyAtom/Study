import QtQuick
import QtQuick.Controls

import com.crazyatom.chatplus

Page {
    id: contactPage

    Component.onCompleted: {
        console.log("contactPage - created")
        listView.currentIndex = SqlConversationsModel.selectedRow
    }

    Component.onDestruction: {
        console.log("contactPage - destroyed")
    }

    header: ChatToolbar {
        height: 40

        ToolButton {
            text: qsTr("New")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: listView.model.add()
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
//        spacing: 5
//        verticalLayoutDirection: ListView.BottomToTop
        clip: true
        cacheBuffer: 2

        model: SqlConversationsModel
        delegate: ItemDelegate {
            width: listView.width - listView.leftMargin - listView.rightMargin; height: avatar.height
            leftPadding: avatar.width + 10
            rightPadding: lastTimestamp.implicitWidth
            bottomPadding: lastMessage.implicitHeight
            highlighted: ListView.isCurrentItem
            text: model.convid
            onClicked: {
                listView.currentIndex = listView.model.selectedRow = index
                if (splitState) {
                    splitView.conversationIdChange(model.convid)
                } else {
                    contactPage.StackView.view.push("qrc:/resources/qml/ConversationPage.qml", { inConversationId: model.convid })
                }
            }

            Image {
                id: avatar
                width: 55; height: 45
                fillMode: Image.PreserveAspectFit
                source: "qrc:/resources/images/chat.svg"
            }

            Label {
                id: lastTimestamp
                width: contentWidth; height: contentHeight
                anchors.right: parent.right
                text: Qt.formatDateTime(model.lasttimestamp, "yy.MM.dd")
                color: "lightgray"
                horizontalAlignment: Text.AlignRight
            }

            Label {
                id: lastMessage
                width: contentWidth; height: contentHeight
                leftPadding: avatar.width + 10
                anchors.bottom: parent.bottom
                text: model.lastmessage
                color: "lightgray"
            }
        }

        ScrollBar.vertical: ScrollBar {}
    }
}
