import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ViewModel

Item {
    anchors.fill: parent

    Component.onCompleted: {
        console.log("StockBook View - created")
    }

    Component.onDestruction: {
        console.log("StockBook View - destroyed")
    }

    StockBookViewModel {
        id: myModel
    }

    ListModel {
        id: addressDataModel

        ListElement { name: "Apple"; market: "2.941 T"; stockPrice: 179.3 }
        ListElement { name: "Microsoft"; market: "2.512 T"; stockPrice: 334.65 }
        ListElement { name: "Google"; market: "1.949 T"; stockPrice: 2947 }
        ListElement { name: "Saudi Aramco"; market: "1.875 T"; stockPrice: 938 }
        ListElement { name: "Amazon"; market: "1.757 T"; stockPrice: 3466 }
        ListElement { name: "Tesla"; market: "980.14 B"; stockPrice: 975.99 }
        ListElement { name: "Meta"; market: "950.41 B"; stockPrice: 341.66 }
        ListElement { name: "NVIDIA"; market: "759.03 B"; stockPrice: 304.59 }
        ListElement { name: "TSMC"; market: "624.40 B"; stockPrice: 120.40 }
    }

    Component {
        id: listViewHeader

        Rectangle {
            id: listHeaderArea
            width: parent.width - listScrollBar.width
            height: 30
            radius: 6
            color: "darkgray"

            Row {
                anchors.fill: parent
                anchors.margins: 3

                Label {
                    width: parent.width * 0.3
                    height: parent.height
                    text: qsTr("Name")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                }

                Label {
                    width: parent.width * 0.2
                    height: parent.height
                    text: qsTr("Market")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignRight
                }

                Label {
                    width: parent.width * 0.5
                    height: parent.height
                    text: qsTr("Stock Price")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignRight
                }
            }
        }
    }

    Component {
        id: listViewDelegate

        Rectangle {
            id: listDelegateArea
            width: parent.width - listScrollBar.width
            height: 40
            color: "transparent"

            Rectangle {
                anchors.fill: parent
                anchors.topMargin: 3
                anchors.bottomMargin: 3
                radius: 6
                border.color: "black"

                MouseArea {
                    id: listMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        if (mylist.currentIndex == index)
                            parent.color = "transparent"
                        else
                            parent.color = "lightBlue"
                    }
                    onExited: parent.color = "transparent"
                    onClicked: {
                        parent.color = "transparent"
                        mylist.currentIndex = index
                        myModel.selectRow(mylist.currentIndex)
                    }
                }

                Row {
                    anchors.fill: parent
                    anchors.margins: 3

                    Label {
                        width: parent.width * 0.3
                        height: parent.height
                        text: model.name
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                    }

                    Label {
                        width: parent.width * 0.2
                        height: parent.height
                        text: model.market
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                    }

                    Label {
                        width: parent.width * 0.5
                        height: parent.height
                        text: model.stockPrice
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                    }
                }
            }
        }
    }

    Component {
        id: highlightBar

        Rectangle {
            width: parent.width
            height: 40
            color: "transparent"

            Rectangle {
                anchors.fill: parent
                anchors.topMargin: 3
                anchors.bottomMargin: 3
                radius: 6
                color: "blue"
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 6
            spacing: 6

            Button {
                id: btnAdd
                Layout.fillWidth: true
                text: qsTr("Add")
            }

            Button {
                id: btnRemove
                Layout.fillWidth: true
                text: qsTr("Remove")
            }

            Button {
                id: bntEdit
                Layout.fillWidth: true
                text: qsTr("Edit")
            }
        }

        Label {
            text: myModel.displayMsg
        }

        ListView {
            id: mylist
            clip: true
            focus: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 6
            ScrollBar.vertical: ScrollBar {
                id: listScrollBar
                policy: ScrollBar.AsNeeded // AlwaysOn
            }

            highlight: highlightBar
            header: listViewHeader
            delegate: listViewDelegate
            model: addressDataModel
        }
    }
}
