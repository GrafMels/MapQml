import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import QtLocation 5.6

Window {
    minimumWidth: 720
    minimumHeight: 540
    visible: true
    title: qsTr("Map")

    property int defMargin: 10
    property var coordinate1: map.toCoordinate(Qt.point(52.11, 104.11))
    property var coordinate2: map.toCoordinate(Qt.point(52.12, 104.12))
    property var coordinateRestArea: map.toCoordinate(Qt.point(52.12, 104.12))

    GridLayout{
        id: loColumn
        anchors.fill: parent
        anchors.margins: defMargin
        columns: 4
        rows: 3
        columnSpacing: defMargin
        rowSpacing: defMargin

        Rectangle{
            width: 700
            height: 300
            Layout.column: 0
            Layout.row: 0
            Layout.columnSpan: 4
            Layout.fillHeight: parent
            Layout.fillWidth: parent

            Map{
                id: map
                plugin: Plugin {name: "osm"}
                center: QtPositioning.coordinate(59.95, 30.5)
                anchors.fill: parent
                zoomLevel: 8

                MapPolyline{
                    id: girosPath
                    path: [{latitude: coordinate1.latitude, longitude: coordinate1.longitude}, {latitude: coordinate2.latitude, longitude: coordinate2.longitude}]
                }

                MapCircle {
                    id: circleStart
                    radius: 200.0
                    color: 'green'
                }

                MapCircle {
                    id: circleEnd
                    radius: 200.0
                    color: 'green'
                }

                MouseArea {
                    acceptedButtons: Qt.LeftButton
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    onClicked:  {
                        coordinate1 = map.toCoordinate(Qt.point(mouse.x, mouse.y))
                        leftClickOnMap(coordinate1.latitude, coordinate1.longitude)
                    }
                }

                MouseArea {
                    acceptedButtons: Qt.RightButton
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    onClicked:  {
                        coordinate2 = map.toCoordinate(Qt.point(mouse.x, mouse.y))
                        rightClickOnMap(coordinate2.latitude, coordinate2.longitude)
                    }
                }

                MouseArea {
                    id: mouseAreaMidle
                    acceptedButtons: Qt.MiddleButton
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    onClicked: {
                        var coordinate = map.toCoordinate(Qt.point(mouse.x, mouse.y))
                        midleClickOnMap(coordinate.latitude, coordinate.longitude)
                    }
                }
            }
        }

        Rectangle {
            Layout.column: 0
            Layout.row: 1
            Layout.columnSpan: 1

            width: 50
            height: 20
            Text{
                text: "Latitude: "
            }
        }

        Rectangle {
            Layout.column: 1
            Layout.row: 1
            Layout.columnSpan: 1

            width: 270
            height: 20

            border.width: 1
            border.color: "gray"
            TextInput{
                id: textLatitude
                validator: RegExpValidator { regExp: /[0-9A-F]+[.]+[0-9A-F]+[0-9A-F]+[0-9A-F]/ }
                width: 270
                height: 20
                text: "59.95"
            }
        }

        Rectangle {
            Layout.column: 2
            Layout.row: 1
            Layout.columnSpan: 1

            width: 50
            height: 20
            Text{
                text: "Longitude: "
            }
        }

        Rectangle {
            Layout.column: 3
            Layout.row: 1
            Layout.columnSpan: 1

            width: 270
            height: 20

            border.width: 1
            border.color: "gray"
            TextInput {
                id: textLongitude
                validator: RegExpValidator { regExp: /[0-9A-F]+[.]+[0-9A-F]+[0-9A-F]+[0-9A-F]/ }
                width: 270
                height: 20
                text: "30.50"
            }
        }

        Button {
            Layout.column: 0
            Layout.row: 2
            Layout.columnSpan: 4

            height: 100
            Layout.fillWidth: true

            text: "Перейти по координатам"
            onClicked: {
                goToCoordinate(textLatitude.text, textLongitude.text);
            }
        }

        Rectangle {
            Layout.column: 0
            Layout.row: 3
            Layout.columnSpan: 2

            width: 100
            height: 20
            Text{
                text: "Radius: "
            }
        }

        Rectangle {
            Layout.column: 2
            Layout.row: 3
            Layout.columnSpan: 2

            width: 320
            height: 20

            border.width: 1
            border.color: "gray"
            TextInput{
                id: textRadiusRestrictedArea
                validator: RegExpValidator { regExp: /[0-9A-F][0-9A-F][0-9A-F][0-9A-F]/ }
                width: 320
                height: 20
                text: "5000"
            }
        }

        Button {
            Layout.column: 0
            Layout.row: 4
            Layout.columnSpan: 4

            height: 100
            Layout.fillWidth: true

            text: "clear"
            onClicked: {
                map.clearMapItems()
            }
        }
    }

    function goToCoordinate(latitude, longitude){
        map.center.latitude = latitude
        map.center.longitude = longitude
    }

    function leftClickOnMap(latitude, longitude){

        console.log("Start: " + coordinate1.latitude + " " + coordinate1.longitude)
        circleStart.center.latitude = latitude
        circleStart.center.longitude = longitude

        wayPoint.pointStartChanged(latitude, longitude);
        wayPoint.pointsReady()
    }

    function rightClickOnMap(latitude, longitude){

        console.log("End: " + coordinate2.latitude + " " + coordinate2.longitude)
        circleEnd.center.latitude = latitude
        circleEnd.center.longitude = longitude

        wayPoint.pointEndChanged(latitude, longitude);
        wayPoint.pointsReady()
    }

    function midleClickOnMap(latitude, longitude){
        restrictedAreaList.addNewResArea(Qt.point(latitude, longitude), textRadiusRestrictedArea.text)
        var component = Qt.createComponent("RestrictedArea.qml")
        var item = null;
        if(component.status === Component.Ready){
            item = component.createObject(map);
            item.center.latitude = latitude
            item.center.longitude = longitude
            item.radius = textRadiusRestrictedArea.text
            map.addMapItem(item)
        }else{
            console.log(component.errorString());
        }
    }

    function addNewArea(poin, radius){
        restrictedAreaList.addNewResArea(Qt.point(latitude, longitude), 5000)
    }

    function addMapLine(latitudeStart, longitudeStart, latitudeEnd, longitudeEnd){
        var component = Qt.createComponent("Point.qml")
        var item = null;
        if(component.status === Component.Ready){
            item = component.createObject(map);
            item.center.latitude = latitudeStart
            item.center.longitude = longitudeStart
            item.radius = 200
            map.addMapItem(item)
        }else{
            console.log(component.errorString());
        }

        component = Qt.createComponent("Point.qml")
        item = null;
        if(component.status === Component.Ready){
            item = component.createObject(map);
            item.center.latitude = latitudeEnd
            item.center.longitude = longitudeEnd
            item.radius = 200
            map.addMapItem(item)
        }else{
            console.log(component.errorString());
        }

        component = Qt.createComponent("Line.qml")
        item = null;
        if(component.status === Component.Ready){
            item = component.createObject(map);
            item.path[0].latitude = latitudeStart
            item.path[0].latitude = longitudeStart
            item.path[1].latitude = latitudeEnd
            item.path[1].latitude = longitudeEnd
            map.addMapItem(item)
        }else{
            console.log(component.errorString());
        }
    }
    Connections{
        target: logic
        onGetMapLine: {
            addMapLine(latitudeStart, longitudeStart, latitudeEnd, longitudeEnd)
        }
    }
}
