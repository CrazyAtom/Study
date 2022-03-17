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
            model: myModel.getListModel();
        }
    }
}
