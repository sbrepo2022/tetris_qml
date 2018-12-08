import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: mw
    visible: true
    width: 540
    height: 960
    title: qsTr("Tetris")

    property double wp: width / 100
    property double hp: height / 100

    function pd() {
        return Screen.pixelDensity;
    }

    StackLayout {
        id: mainStackLayout
        currentIndex: 0
        anchors.fill: parent

        Item {
            id: page1
            ColumnLayout {
                id: startLayout
                x: 20 * mw.wp
                y: 20 * mw.hp
                width: 60 * mw.wp
                height: 60 * mw.hp

                Button {
                    id: singleplayerButton
                    anchors.left: parent.left
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: qsTr("Одиночная игра")
                    font.pointSize: 25

                    onClicked: {
                        mainStackLayout.currentIndex = 2
                    }
                }

                Button {
                    id: multiplayerButton
                    anchors.left: parent.left
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: qsTr("Мультиплеер")
                    font.pointSize: 25

                    onClicked: {
                        mainStackLayout.currentIndex = 1
                    }
                }
            }
        }

        Item {
            id: page2
            ColumnLayout {
                id: connectionLayout
                x: 20 * mw.wp
                y: 20 * mw.hp
                width: 60 * mw.wp
                height: 60 * mw.hp

                Button {
                    id: connectButton
                    anchors.left: parent.left
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: qsTr("Присоединиться")
                    font.pointSize: 25
                }

                Button {
                    id: createButton
                    anchors.left: parent.left
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: qsTr("Создать")
                    font.pointSize: 25
                }
            }
        }

        Item {
            id: page3

            Rectangle {
                id: fieldRectangle
                x: 2 * mw.wp
                y: 2 * mw.wp
                width: 96 * mw.wp
                height: 90 * mw.hp - 4 * mw.wp

                color: "#eee"
                border.width: 0

                DropShadow {
                    anchors.fill: parent
                    radius: 10
                    color: "#000"
                    samples: 12
                    source: fieldRectangle
                }
            }

            RowLayout {
                id: controlsLayout
                x: 0
                y: mw.height - 10 * mw.hp
                width: mw.width
                height: 10 * mw.hp

                Button {
                    id: turnLeftButton
                    text: qsTr("")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    padding: 0
                }

                Button {
                    id: moveLeftButton
                    text: qsTr("")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    padding: 0
                }

                Button {
                    id: nextButton
                    text: qsTr("")
                    padding: 0
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                }

                Button {
                    id: moveRightButton
                    text: qsTr("")
                    padding: 0
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                }

                Button {
                    id: turnRightButton
                    text: qsTr("")
                    padding: 0
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                }
            }
        }
    }

}
