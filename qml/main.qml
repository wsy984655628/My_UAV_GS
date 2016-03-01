import Qt3D 2.0
import Qt3D.Renderer 2.0
import QtQuick 2.5 as Quick
Entity
{
    id: root

    Camera
    {
        id: camera
        position: Qt.vector3d( 0.0, 20.0, 100.0 )
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 90
        aspectRatio: 16.0 / 9.0
        nearPlane : 0.1
        farPlane : 1000.0
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 20.0, 0.0 )
    }

    components: FrameGraph
    {
        ForwardRenderer
        {
            clearColor: Qt.rgba( 0, 0, 0, 1 )
            camera: camera
        }
    }

    Entity
    {
        Mesh
        {
            id: chestMesh
            source: "qrc:/assets/Chest.obj"
        }

        Transform{
            id: chestTransform

            Rotate{
                axis:Qt.vector3d(1,0,0)
//                angle:0
                angle:_settings.Pitch
            }
            Rotate{
                axis: Qt.vector3d(0,0,1)
//                angle:0
                angle:_settings.Roll
            }
            Rotate{
                axis:Qt.vector3d(0,1,0)
                angle:_settings.Yaw
//                angle:0
            }
        }

        components: [chestMesh,chestTransform]
    }
    Configuration
    {
    //    controlledCamera: camera
    }
}
