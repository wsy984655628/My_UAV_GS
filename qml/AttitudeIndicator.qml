import QtQuick 2.4

Item {
    id: root

    property bool active: true
    property real rollAngle: _defaultRollAngle
    property real pitchAngle: _defaultPitchAngle
    property bool showPitch: true

    readonly property real _defaultRollAngle:  0
    readonly property real _defaultPitchAngle: 0

    property real _rollAngle: active ? rollAngle : _defaultRollAngle
    property real _pitchAngle: active ? pitchAngle : _defaultPitchAngle

    anchors.centerIn: parent

    width: parent.width
    height: parent.height

    Image {
        id: rollDial
        anchors {
            bottom: root.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        source:     "qrc:/FlightMap/rollDialWhite.svg"
        mipmap:     true
        width:      parent.width
        fillMode:   Image.PreserveAspectFit
        transform:  Rotation {
            origin.x:   rollDial.width / 2
            origin.y:   rollDial.height
            angle:      -_rollAngle
        }
    }

    Image {
        id: pointer
        anchors {
            bottom: root.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        source:     "qrc:/FlightMap/rollPointerWhite.svg"
        mipmap:     true
        width:      rollDial.width
        fillMode:   Image.PreserveAspectFit
    }
    PitchIndicator{
        id: pitchIndicator
        anchors.verticalCenter: parent.verticalCenter
        pitchAngle: _pitchAngle
        rollAngle: _rollAngle
        size: parent.width > 300? 300 * 10 / 23 : parent.width * 10 / 23
    }
    Image   {
        id: crossHair
        anchors.centerIn: parent
        source:     "qrc:/FlightMap/crossHair.svg"
        mipmap:     true
        width:      parent.width
        fillMode:   Image.PreserveAspectFit
    }
}

