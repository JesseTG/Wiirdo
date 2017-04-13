import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import wii 1.0

Item {

    Wii {
      id: wii

      Component.onCompleted: {
        console.log("Ready to go");
      }
    }

    id: item1
    width: 400
    height: 400
    property alias gridLayout: gridLayout
    property alias frame: frame

    Frame {
        id: frame
        anchors.fill: parent
        opacity: 1
        visible: true
        clip: true
        spacing: 2
        padding: 13

        GridLayout {
            id: gridLayout
            anchors.fill: parent
            columnSpacing: 6
            rowSpacing: 5
            columns: 2

            Text {
                id: text1
                width: 155
                height: 40
                text: qsTr("Gesture_1")
                font.pixelSize: 12
            }

            ComboBox {
                id: comboBox
                width: 168
                height: 40
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                model: ["First", "Second", "Third"]
            }

            Text {
                id: text2
                width: 155
                height: 40
                text: qsTr("Gesture_2")
                font.pixelSize: 12
            }

            ComboBox {
                id: comboBox1
                width: 168
                height: 40
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                model: ["First", "Second", "Third"]
            }

            Text {
                id: text3
                width: 155
                height: 42
                text: qsTr("Gesture_3")
                font.pixelSize: 12
            }

            ComboBox {
                id: comboBox2
                width: 168
                height: 40
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                model: ["First", "Second", "Third"]
            }

            Text {
                id: text4
                width: 155
                height: 40
                text: qsTr("Gesture_4")
                font.pixelSize: 12
            }

            ComboBox {
                id: comboBox3
                width: 168
                height: 40
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                model: ["First", "Second", "Third"]
            }

            Button {
                id: button1
                width: 344
                height: 31
                text: qsTr("Activate")
                onReleased: {
                    wii.click();
                    console.log("QML");
                }
            }
        }
    }
}
