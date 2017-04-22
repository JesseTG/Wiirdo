import QtQuick 2.7
import QtQuick.Window 2.2
import QtCanvas3D 1.1
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick.Scene3D 2.0
import QtQuick.Controls 2.1

import wii 1.0

Item {

  Wii {
    id: wii

    Component.onCompleted: {
      console.log("Ready to go");
    }

    onConnectionSucceeded: {
      var wiimote = wii.wiimotes[0];

      wiimote.accelerometerEnabled = true;
      wiimote.smoothingEnabled = true;

      accelerationThreshold.value = wiimote.accelerometer.accelerationThreshold;
      orientationThreshold.value = wiimote.accelerometer.orientationThreshold * 100;

      wiimoteTest.pollTimer.start();
    }

    onConnectionFailed: {
      console.log("Found no Wiimotes");
    }

    onConnectionDone: {
      searchButton.text = "Find Wiimote";
      searchButton.enabled = true;
    }
  }

  Rectangle {
      id: scene
      anchors.fill: parent
      anchors.margins: 0
      color: "darkRed"

      transform: Rotation {
          id: sceneRotation
          axis.x: 1
          axis.y: 0
          axis.z: 0
          origin.x: scene.width / 2
          origin.y: scene.height / 2
      }

      Rectangle {
        id: gui
        color: "blue"

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        height: parent.height * 0.2

        Text {
          id: statsLabel
          anchors.left: parent.left
          color: 'white'
          font.pointSize: 14
          font.family: "Courier"
          font.bold: true
          text: {
            if (wii.wiimotes.length === 0) {
              return "No Wiimotes connected";
            }

            var wiimote = wii.wiimotes[0];
            var gravity = wiimote.accelerometer.gravity;
            var gravityRaw = wiimote.accelerometer.gravityRaw;
            var orientation = wiimote.accelerometer.orientation;
            return "Gravity: (%1, %2, %3)\n"
              .arg(gravity.x.toFixed(2))
              .arg(gravity.y.toFixed(2))
              .arg(gravity.y.toFixed(2)) +
            "Gravity (Raw): (%1, %2, %3)\n"
              .arg(gravityRaw.x.toFixed(2))
              .arg(gravityRaw.y.toFixed(2))
              .arg(gravityRaw.z.toFixed(2)) +
            "Orientation: (Pitch=%1, Roll=%2, Yaw=%3)\n"
              .arg(orientation.x.toFixed(2))
              .arg(orientation.y.toFixed(2))
              .arg(orientation.z.toFixed(2)) +
            "A held: %1".arg(wiimote.aHeld);
          }
        }

        Text {
          id: fixedStatsLabel
          anchors.left: parent.left
          anchors.bottom: parent.bottom
          color: 'white'
          font.pointSize: 14
          font.family: "Courier"
          font.bold: true

          text: {
            if (wii.wiimotes.length === 0) {
              return "";
            }

            var wiimote = wii.wiimotes[0];
            var id = wiimote.id;
            var address = wiimote.address;
            var battery = wiimote.battery;

            return "ID: %1\nAddress: %2\nBattery: %3%"
              .arg(id)
              .arg(address)
              .arg((battery * 100).toFixed())
          }
        }

        Button {
          id: searchButton
          text: "Find Wiimote"
          anchors.top: parent.top
          anchors.right: parent.right
          onClicked: {
            console.log("Looking for wiimotes");
            searchButton.text = "Searching...";
            searchButton.enabled = false;
            wii.findAndConnect();
          }
        }

        Rectangle {
          id: accelerationThresholdGroup

          anchors.top: searchButton.bottom
          anchors.right: parent.right
          height: 64

          Text {
            id: accelerationThresholdLabel
            color: 'white'
            font.pointSize: 14
            font.family: "Courier"
            font.bold: true
            verticalAlignment: Text.AlignVCenter

            text: "Accel. Threshold"
            anchors.right: accelerationThreshold.left
          }

          SpinBox {
            id: accelerationThreshold
            anchors.right: parent.right
            editable: true
          }
        }

        Rectangle {
          id: orientationThresholdGroup
          anchors.top: accelerationThresholdGroup.bottom
          anchors.right: parent.right

          Text {
            id: orientationThresholdLabel
            color: 'white'
            font.pointSize: 14
            font.family: "Courier"
            font.bold: true
            verticalAlignment: Text.AlignVCenter

            text: "Orientation Threshold"
            anchors.right: orientationThreshold.left
          }

          SpinBox {
            id: orientationThreshold
            anchors.right: parent.right
            editable: true
          }
        }
      }

      Scene3D {
          id: scene3d
          anchors.top: gui.bottom
          anchors.left: parent.left
          anchors.right: parent.right
          anchors.bottom: parent.bottom
          aspects: ["input", "logic"]
          cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

          WiimoteTest {
            id: wiimoteTest
            wii: wii
            accelerationThreshold: accelerationThreshold.value
            orientationThreshold: orientationThreshold.value / 100
          }
      }
  }
}
