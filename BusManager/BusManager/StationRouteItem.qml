import QtQuick 2.15

Item {
    property int p_referHeight: 50
    property string v_stationRouteName: "Tuyến số 53"
    property string v_mainStationsName: "Bến Xe Buýt Sài Gòn - Khu Chế Xuất Linh Trung - Đại Học Quốc Gia"
    property bool v_directionForward: true
    property int v_routeStatus: 0
    property int v_index: 0

    height: stationRouteItemWrap.height

    Rectangle{
        id: stationRouteItemWrap
        width: parent.width
        height: busIconWrap.height + stationRouteInfo.height + routeStatusWrap.height + busListView.height + p_referHeight * 0.85
        anchors.top: parent.top
        radius: p_referHeight * 0.3
        color: "#f7f7f7"

        Rectangle{
            id: busIconWrap
            width: parent.width*0.15
            height: stationRouteInfo.height
            color: parent.color
            anchors.top: parent.top
            anchors.topMargin: p_referHeight / 4
            Image {
                id: busIcon
                height: p_referHeight * 0.8
                width: height
                anchors.horizontalCenter: parent.horizontalCenter
                source: "./Images/busIcon.svg"
            }
        }
        Rectangle{
            id: stationRouteInfo
            width: parent.width*0.85
            height: stationRouteNameWrap.height + mainStationsNameWrap.height
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: p_referHeight / 5
            color: "transparent"
            Rectangle{
                id: stationRouteNameWrap
                width: parent.width
                height: stationRouteName.height
                anchors.left: parent.left
                color: parent.color
                Text {
                    id: stationRouteName
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width/20
                    font.pixelSize: p_referHeight*0.4
                    font.bold: true
                    text: v_stationRouteName
                }
                Text {
                    id: directionName
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width/20
                    font.pixelSize: p_referHeight*0.4
                    text: v_directionForward ? "ĐIỂM ĐI" : "ĐIỂM ĐẾN"
                    color: v_directionForward ? "#007bff" : "#008662"
                }
            }
            Rectangle{
                id: mainStationsNameWrap
                width: parent.width
                height: mainStationsName.height
                anchors.top: stationRouteNameWrap.bottom
                anchors.left: parent.left
                color: parent.color
                Text {
                    id: mainStationsName
                    width: parent.width
                    leftPadding: parent.width/20
                    wrapMode: Text.WordWrap
                    font.pixelSize: p_referHeight * 0.35
                    text: v_mainStationsName
                }
            }
        }
        Rectangle{
            id: routeStatusWrap
            width: parent.width
            height: p_referHeight * 0.8
            anchors.top: stationRouteInfo.bottom
            anchors.left: parent.left
            anchors.topMargin: p_referHeight / 4
            color: "#f1f1f1"
            Rectangle{
                id: pointStatusWrap
                width: parent.height
                height: parent.height
                color: parent.color
                Rectangle{
                    id: routeStatusIcon
                    width: parent.width/3
                    height: width
                    radius: width*0.5
                    color: (v_routeStatus == 0) ? "#8998AC" : "green"
                    anchors.centerIn: parent
                }
            }
            Rectangle{
                id: detailStatusWrap
                width: parent.width - parent.height
                height: parent.height
                anchors.left: pointStatusWrap.right
                color: parent.color
                Text {
                    id: detailStatusText
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: p_referHeight * 0.35
                    anchors.left: parent.left
                    anchors.leftMargin: p_referHeight / 5
                    text: (v_routeStatus == 0) ? "Chưa hoạt động" : "Đang hoạt động"
                }
            }
        }

        ListModel {
            id: route1
            ListElement {
                busid: "51B-251.87"
                arrivalTime: 5
                busSpeed: 30
                busDistance: 1.2
            }
            ListElement {
                busid: "51B-251.88"
                arrivalTime: 23
                busSpeed: 0
                busDistance: 0.6
            }
            ListElement {
                busid: "51B-251.89"
                arrivalTime: 231
                busSpeed: 011
                busDistance: 10.6
            }
        }

        ListView{
            id: busListView
            width: parent.width
            anchors.top: routeStatusWrap.bottom
            anchors.topMargin: p_referHeight * 0.2
            model: BusModel.BusRouteList[v_index].NoBusItem// route1
            height:  p_referHeight * (count - 1)
            interactive: false

            delegate:
                Rectangle{
                width: parent.width
                height: p_referHeight
                StationVehicleItem{
                    id: vbus1
                    referHeight: p_referHeight
                    width: parent.width
                    v_busid: BusModel.BusRouteList[v_index].BusItemList[index].BusId //model.BusId // busid
                    v_busSpeed: BusModel.BusRouteList[v_index].BusItemList[index].Speed //model.Speed // busSpeed
                    v_arrivalTime: BusModel.BusRouteList[v_index].BusItemList[index].TimeArrival // arrivalTime
                    v_busDistance: BusModel.BusRouteList[v_index].BusItemList[index].Distance //model.Peoples // busDistance
                    v_Temperature: BusModel.BusRouteList[v_index].BusItemList[index].Temperature
                    v_Huminity: BusModel.BusRouteList[v_index].BusItemList[index].Huminity
                    v_Peoples: BusModel.BusRouteList[v_index].BusItemList[index].Peoples
                }
            }
        }
    }
}
