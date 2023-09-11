import QtQuick 2.15
import QtLocation 5.6

MapPolyline{
    property alias mainPolyline: girosPath
    id: girosPath
    line.width: 5
}
