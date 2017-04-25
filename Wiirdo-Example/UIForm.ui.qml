import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles.Desktop 1.0
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 400
    height: 400
    property alias frame: frame

    Frame {
        id: frame
        x: 15
        width: 370
        height: 281
        opacity: 1
        visible: true
        clip: true
        anchors.top: parent.top
        anchors.topMargin: 60
        spacing: 2
        padding: 13

        ColumnLayout {
            id: columnLayout
            x: -13
            y: -13
            width: 370
            height: 288
        }

        ComboBox {
            id: comboBox
            x: 176
            y: 14
            width: 168
            height: 40
            model: ["First", "Second", "Third"]
        }

        ComboBox {
            id: comboBox1
            x: 176
            y: 60
            width: 168
            height: 40
            model: ["First", "Second", "Third"]
        }

        ComboBox {
            id: comboBox2
            x: 176
            y: 108
            width: 168
            height: 40
            model: ["First", "Second", "Third"]
        }

        ComboBox {
            id: comboBox3
            x: 176
            y: 154
            width: 168
            height: 40
            model: ["First", "Second", "Third"]
        }

        Text {
            id: text1
            x: 0
            y: 14
            width: 155
            height: 40
            text: qsTr("Gesture_1")
            font.pixelSize: 12
        }

        Text {
            id: text2
            x: 0
            y: 60
            width: 155
            height: 40
            text: qsTr("Gesture_2")
            font.pixelSize: 12
        }

        Text {
            id: text3
            x: 0
            y: 106
            width: 155
            height: 42
            text: qsTr("Gesture_3")
            font.pixelSize: 12
        }

        Text {
            id: text4
            x: 0
            y: 154
            width: 155
            height: 40
            text: qsTr("Gesture_4")
            font.pixelSize: 12
        }

        Button {
            id: button
            x: 0
            y: 218
            width: 344
            height: 31
            text: qsTr("Activate")
        }
    }
}
