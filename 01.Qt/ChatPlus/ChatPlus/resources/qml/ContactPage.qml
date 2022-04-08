import QtQuick
import QtQuick.Controls

import com.crazyatom.chatplus

Page {
    id: root

    header: ChatToolbar {
        ToolButton {
            text: qsTr("New")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                listView.model.add();
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        spacing: 5
//        verticalLayoutDirection: ListView.BottomToTop
        clip: true
        cacheBuffer: 2
        model: SqlConversationsModel {}
        delegate: ItemDelegate {
            text: model.convid
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: avatar.height
            leftPadding: avatar.width + 10
            onClicked: root.StackView.view.push("qrc:/resources/qml/ConversationPage.qml", { inConversationId: model.convid })

            Image {
                id: avatar
                width: 55; height: 45
                fillMode: Image.PreserveAspectFit
                source: "qrc:/resources/images/chat.svg"
            }
        }

        ScrollBar.vertical: ScrollBar {}
    }
}
