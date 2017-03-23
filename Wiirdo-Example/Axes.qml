import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Entity {
  CuboidMesh {
    id: axisMesh
  }

  Entity {
    id: xAxis

    Transform {
      id: xTransform
      scale3D: Qt.vector3d(40, 1, 1)
    }
    PhongMaterial {
      id: xMaterial
      diffuse: 'red'
    }

    components: [xTransform, xMaterial, axisMesh]
  }

  Entity {
    id: yAxis

    Transform {
      id: yTransform
      scale3D: Qt.vector3d(1, 40, 1)
    }
    PhongMaterial {
      id: yMaterial
      diffuse: 'blue'
    }

    components: [yTransform, yMaterial, axisMesh]
  }

  Entity {
    id: zAxis

    Transform {
      id: zTransform
      scale3D: Qt.vector3d(1, 1, 40)
    }
    PhongMaterial {
      id: zMaterial
      diffuse: 'green'
    }

    components: [zTransform, zMaterial, axisMesh]
  }
}
