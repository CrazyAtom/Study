import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import App 1.0

Row {

    property var parentWidth

    function validWidth(width) {
        var validW = parentWidth - date.implicitWidth
        return (validW > width) ? width : validW
    }

    height: implicitHeight
    spacing: 5
    padding: 5

    Rectangle {
        id: messageArea
        width: message.implicitWidth
        height: message.implicitHeight
        anchors.verticalCenter: parent.verticalCenter
        color: "#33393F"
        radius: 6

        Text {
            id: message
            text: modelData.message
            width: contentWidth
//            height: contentHeight
            padding: 10
            color: "#FFFFFF"
            font.pixelSize: 13
//            wrapMode: Text.Wrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }

    Text {
        id: date
        text: modelData.date
        width: contentWidth
        anchors.verticalCenter: parent.verticalCenter
        color: "#727C83"
        font.pixelSize: 10
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }
}






//Rectangle {
//    id: stringItemDelegateArea
//    width: implicitWidth
//    height: 30//contentArea.height
//    color: "transparent"

//    function validContentWidth() {
//        var width = stringItemDelegateArea.width - date.width
//        return width
//    }

//    function validContentHeight() {
//        var height = contentArea.height < 30 ? 30 : contentArea.height
////        console.log("validContentHeight: ", height)
//        return height
//    }

//    Rectangle {
//        id: contentArea
//        anchors { fill: parent; margins: 5 }
////        anchors { left: parent.left; right: parent.right; margins: 5 }
////        height: messageArea.height + 5
//        color: "transparent"

//        Row {
//            anchors.fill: parent
//            spacing: 5

//            Rectangle {
//                id: messageArea
//                width: message.width + message.padding
//                height: message.height + message.padding
//                anchors.verticalCenter: parent.verticalCenter
//                antialiasing: true
//                radius: 6
//                color: "gray"

//                Text {
//                    id: message
//                    width: contentWidth
//                    height: contentHeight
//                    font.pixelSize: 13
//                    text: modelData.message
//                    color: "white"
//                    padding: 5
//                    verticalAlignment: Text.AlignVCenter
//                    horizontalAlignment: Text.AlignLeft
////                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                }
//            }

//            Label {
//                id: date
//                width: contentWidth
//                anchors { top: parent.top; bottom: parent.bottom; }
//                font.pixelSize: 10
//                text: modelData.date
//                color: "lightgray"
//                verticalAlignment: Text.AlignBottom
//                horizontalAlignment: Text.AlignLeft
//            }
//        }
//    }
//}
