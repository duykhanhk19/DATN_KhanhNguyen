import QtQuick 2.15
import QtLocation 5.9
import QtPositioning 5.5

Item {
    property variant locationOslo: QtPositioning.coordinate(10.881277, 106.808979)

    Rectangle{
        anchors.fill: parent
        color: "transparent"
        Plugin {
            id: mapPlugin
            name: "osm"
        }

        PlaceSearchModel {
            id: searchModel

            plugin: mapPlugin

            searchTerm: "Cafe"
            searchArea: QtPositioning.circle(locationOslo)

            Component.onCompleted: update()
        }

        RouteModel {
            id: routeModel
            plugin: mapPlugin
            query: RouteQuery {}
            Component.onCompleted: {
                query.addWaypoint(QtPositioning.coordinate(10.881298, 106.808990));
                query.addWaypoint(QtPositioning.coordinate(10.877884, 106.807348));
                query.addWaypoint(QtPositioning.coordinate(10.878390, 106.806168));
                query.addWaypoint(QtPositioning.coordinate(10.880518, 106.805406));
                routeModel.update();
            }
        }

        Map {
            id: main_map
            width: parent.width * 3/4
            height: parent.height
            anchors.right: parent.right
            plugin: mapPlugin
            center: QtPositioning.coordinate(10.880335, 106.804683)
            zoomLevel: 15
            MapItemView {
                id: mapview1
                visible: false
                model: 1
                delegate: MapQuickItem {
                    coordinate: locationOslo

                    anchorPoint.x: image.width * 0.5
                    anchorPoint.y: image.height

                    sourceItem: Column {
                        Image { id: image; source: "/Images/markerMapIcon.png"; width: 20; height: width }
                    }
                }
            }
            MapItemView {
                id: mapview2
                visible: false
                model: routeModel
                delegate: MapRoute {
                    route: routeData
                    line.color: "blue"
                    line.width: 5
                    smooth: true
                }
            }
        }
    }
}
