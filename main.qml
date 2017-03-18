import QtQuick 2.7
import QtQuick.Window 2.2
import QtCanvas3D 1.1
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick.Scene3D 2.0

import wii 1.0

Item {

  Wii {
    id: wii

    Component.onCompleted: {
      console.log("Looking for wiimotes");
      wii.findAndConnect();

    }

    onConnectionSucceeded: {
      wii.wiimotes[0].accelerometerEnabled = true;
      wiimoteTest.pollTimer.start();
    }

    onConnectionFailed: {
      console.log("Found no Wiimotes");
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
          return "Gravity: (%1, %2, %3)\nGravity (Raw): (%4, %5, %6)\nOrientation: (Pitch=%7, Roll=%8, Yaw=%9)"
            .arg(gravity.x.toFixed(2))
            .arg(gravity.y.toFixed(2))
            .arg(gravity.y.toFixed(2))
            .arg(gravityRaw.x.toFixed(2))
            .arg(gravityRaw.y.toFixed(2))
            .arg(gravityRaw.z.toFixed(2))
            .arg(orientation.x.toFixed(2))
            .arg(orientation.y.toFixed(2))
            .arg(orientation.z.toFixed(2));
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

      Scene3D {
          id: scene3d
          anchors.fill: parent
          anchors.margins: 10
          focus: true
          cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

          WiimoteTest {
            id: wiimoteTest
            wii: wii
          }
      }
  }
}
