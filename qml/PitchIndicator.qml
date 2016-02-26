import QtQuick 2.0
import QtQuick.Window 2.0

Item{
    property real pitchAngle: 0
    property real rollAngle:  0
    property real size: 100
    property real _longDash:  size * 0.40
    property real _shortDash: size * 0.25

    height: size
    width: size
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    clip: true

    Item{
        height: parent.height
        width: parent.width
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: size * 0.15
            Repeater{
                model: 36
                Rectangle{
                    property int _pitch: -(modelData * 5 - 90)
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: (_pitch % 10) === 0 ? _longDash : _shortDash
                    height: 1
                    color: "white"
                    antialiasing: true
                    smooth: true
                    QGCLabel{
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.horizontalCenterOffset: -(_longDash * 0.8)
                        anchors.verticalCenter: parent.verticalCenter
                        smooth: true
                        font.weight: Font.DemiBold
                        text: _pitch
                        color: "white"
                        visible: (_pitch != 0) && ((_pitch % 10) === 0)
                    }
                    QGCLabel{
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.horizontalCenterOffset: (_longDash * 0.8)
                        anchors.verticalCenter: parent.verticalCenter
                        smooth: true
                        font.weight: Font.DemiBold
                        text: _pitch
                        color: "white"
                        visible: (_pitch != 0) && ((_pitch % 10) === 0)
                    }
                }
            }
        }
        transform: [Translate {
            y: (pitchAngle * (size * 0.15 + 1) / 5) - ((size * 0.15 + 1) / 2)
            }
        ]
    }
    transform: [
        Rotation{
            origin.x: width / 2
            origin.y: height / 2
            angle: -rollAngle
        }

    ]
}

