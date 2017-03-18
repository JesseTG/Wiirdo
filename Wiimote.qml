import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

import QtQuick 2.0 as QQ2

Entity {
    id: wiimote
    components: [wiimoteMesh, material, wiimoteTransform]

    property alias transform: wiimoteTransform

    DiffuseMapMaterial {
        id: material
        diffuse: "data/wiimote.jpg"
    }

    Mesh {
        id: wiimoteMesh
        source: "data/wiimote.obj"
    }

    Transform {
        id: wiimoteTransform
        scale: 3
    }
}
