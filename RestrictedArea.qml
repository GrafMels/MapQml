import QtQuick 2.15
import QtLocation 5.6

MapCircle {
    id: restrictedArea
    radius: 5000.0
    color: 'red'
    MouseArea {
        id: mouseAreaMidle
        acceptedButtons: Qt.MiddleButton
        anchors.fill: parent
        onClicked: {
            mouseAreaMidle.destroy()
            map.removeMapItem(restrictedArea)
        }
    }
}


