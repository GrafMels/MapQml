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
                center: QtPositioning.coordinate(59.9386, 30.3141)
                anchors.fill: parent
                zoomLevel: 10

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
                    radius: 200
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
        circleStart.center.latitude = latitude
        circleStart.center.longitude = longitude

        wayPoint.pointStartChanged(latitude, longitude);
        wayPoint.pointsReady()
    }

    function rightClickOnMap(latitude, longitude){
        circleEnd.center.latitude = latitude
        circleEnd.center.longitude = longitude

        wayPoint.pointEndChanged(latitude, longitude);
        wayPoint.pointsReady()
    }

    function midleClickOnMap(latitude, longitude){
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

        var coordinateCircleX = QtPositioning.coordinate(latitude, longitude).atDistanceAndAzimuth(textRadiusRestrictedArea.text, 0)
        var coordinateCircleY = QtPositioning.coordinate(latitude, longitude).atDistanceAndAzimuth(textRadiusRestrictedArea.text, 90)
        restrictedAreaList.addNewResArea(Qt.point(latitude, longitude), Qt.point(coordinateCircleX.latitude, coordinateCircleX.longitude), Qt.point(coordinateCircleY.latitude, coordinateCircleY.longitude))
    }

    function addNewArea(poin, radius){
        restrictedAreaList.addNewResArea(Qt.point(latitude, longitude), 5000)
    }

    function addMapLine(latitudeStart, longitudeStart, latitudeEnd, longitudeEnd){
        var component = Qt.createComponent("Point.qml")
        var item1 = null;
        var item2 = null;
        var item3 = null;
        if(component.status === Component.Ready){
            item1 = component.createObject(map);
            item1.center.latitude = latitudeStart
            item1.center.longitude = longitudeStart
            item1.radius = 500
            map.addMapItem(item1)
        }else{
            console.log(component.errorString());
        }

        component = Qt.createComponent("Point.qml")
        if(component.status === Component.Ready){
            item2 = component.createObject(map);
            item2.center.latitude = latitudeEnd
            item2.center.longitude = longitudeEnd
            item2.radius = 500
            map.addMapItem(item2)
        }else{
            console.log(component.errorString());
        }

        component = Qt.createComponent("Line.qml")
        if(component.status === Component.Ready){
            item3 = component.createObject(map);
            item3.path = [{latitude: latitudeStart, longitude: longitudeStart}, {latitude: latitudeEnd, longitude: longitudeEnd}]
            item3.line.width = 2
            map.addMapItem(item3)
        }else{
            console.log(component.errorString());
        }
    }

    function addPoint(latitude, longitude){
        var component = Qt.createComponent("Point.qml")
        var item = null;
        if(component.status === Component.Ready){
            item = component.createObject(map);
            item.center.latitude = latitude
            item.center.longitude = longitude
            item.radius = 200
            item.color = "purple"
            map.addMapItem(item)
        }else{
            console.log(component.errorString());
        }
    }

    Connections{
        target: logic
        onGetMapLine: {
            addMapLine(x1, y1, x2, y2)
        }
    }

    Connections{
        target: logic
        onPrintPoint: {
            addPoint(x, y)
        }
    }
}
