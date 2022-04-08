import QtQuick
import QtQuick.Controls

Row {
    id: splitView
    anchors.fill: parent

    Component.onCompleted: {
        console.log("splitView - created")
    }

    Component.onDestruction: {
        console.log("splitView - destroyed")
    }

    signal conversationIdChange(string convid);

    Connections {
        target: splitView
        onConversationIdChange: {
            rightPage.inConversationId = convid;
            console.log("onConversationIdChange: " + convid)
        }
    }

    ContactPage {
        id: leftPage;
        width: parent.width * 0.3; height: parent.height
    }

    ConversationPage {
        id: rightPage;
        width: parent.width * 0.7; height: parent.height
    }
}
