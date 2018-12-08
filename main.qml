import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: mw
    visible: true
    width: 540
    height: 960
    title: qsTr("Tetris")

    property double ws: width / 100
    property double hs: height / 100
    property int pd: Screen.pixelDensity

    TextEdit {
        id: textEdit;
        x: 0
        y: 0
        width: 90 * mw.ws
        height: 10 * mw.ws
    }

    Button {
        id: button1

        x: 90 * mw.ws
        y: 0
        width: 10 * mw.ws
        height: 10 * mw.ws

        onClicked: {
            TetrisCppCore.onTextChange(textEdit.text + "!");
        }
    }

    Connections {
        target: TetrisCppCore

        onSetText: {
            textEdit.text = text;
        }
    }
}
