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
//            onClicked:
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        spacing: 2
        cacheBuffer: 2
        model: SqlContactModel {}
        delegate: ItemDelegate {
            property int indexOfThisDelegate: index

            text: model.display
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: avatar.height
            leftPadding: avatar.width + 32
            onClicked: root.StackView.view.push("qrc:/resources/qml/ConversationPage.qml", { inConversationWith: modelData, recipientAvatar: avatar.source })

            Image {
                id: avatar

                readonly property int index: parent.indexOfThisDelegate + 1

                width: 40; height: 40
                fillMode: Image.PreserveAspectFit
                source: "qrc:/avatar/resources/images/avatar_" + index + ".svg"
            }
        }
    }
}
