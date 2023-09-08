import QtQuick 2.15
import QtLocation 5.6

MapPolyline{
    id: girosPath
    path: [{latitude: coordinate1.latitude, longitude: coordinate1.longitude}, {latitude: coordinate2.latitude, longitude: coordinate2.longitude}]
}
