import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

import QtQuick 2.0

import wii 1.0

Entity {
    id: sceneRoot

    property Wii wii
    property alias pollTimer: pollTimer

    Timer {
      id: pollTimer
      repeat: true
      interval: 16
      triggeredOnStart: true
      onTriggered: {
        wii.poll();

        var orientation = wii.wiimotes[0].accelerometer.orientation;

        wiimote.transform.rotationX = orientation.x - 90;
        wiimote.transform.rotationY = orientation.y;
        wiimote.transform.rotationZ = orientation.z;
      }
    }

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane: 0.1
        farPlane: 1000.0
        position: Qt.vector3d(0.0, 0.0, 40.0)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
    }

    FirstPersonCameraController {
        camera: camera
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "transparent"
            }
        },
        InputSettings {
        },
        DirectionalLight {
          id: light
          intensity: 0.9
          color: 'white'
          worldDirection: Qt.vector3d(1, -4, -4)
        }
    ]

    Axes {

    }

    Wiimote {
      id: wiimote
    }
}
