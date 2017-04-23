import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import wii 1.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Templates 2.1
import QtQuick.Window 2.2
import QtQuick.Controls.Styles.Desktop 1.0
import Qt.labs.calendar 1.0
import QtQuick.Controls 1.4

Item {

    Wii {
        id: wii

        //Component.onCompleted: {
        //console.log("Ready to go");
        //}
    }

    id: item1
    width: 600
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
                activeFocusOnPress: true
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 200
                model: ["Play", "Pause", "Next", "Previous"]
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
                activeFocusOnPress: true
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 200
                model: ["Play", "Pause", "Next", "Previous"]
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
                activeFocusOnPress: true
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 200
                model: ["Play", "Pause", "Next", "Previous"]
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
                activeFocusOnPress: true
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 200
                model: ["Play", "Pause", "Next", "Previous"]
            }

            Button {
                id: button1
                width: 344
                height: 31
                text: qsTr("Activate")
            }
        }
    }
}
