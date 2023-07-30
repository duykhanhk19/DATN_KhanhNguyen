import QtQuick 2.3

Item {
    property bool v_routeListEnable: true
    property int v_infoOption: 1

    Rectangle{
        id: routeInfoWrap
        height: parent.height
        width: parent.width
        color: "white"
        Rectangle{
            id: stationTitle
            width: parent.width
            height: parent.height/20
            color: parent.color
            Rectangle{
                id: backIconWrap
                height: parent.height
                width: height
                Image {
                    id: backIcon
                    source: "./Images/backButton.png"
                    height: parent.height/1.5
                    width: height
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        //main_listRoute.visible = true
                        //main_stationInfo.visible = false
                        //main_map.visible = true
                        //main_webview.visible = true
                        //main_webview.reload()
                    }
                }
            }
            Rectangle{
                id: stationNameWrap
                anchors.left: backIconWrap.right
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - backIconWrap.width
                height: parent.height
                color: parent.color
                Text {
                    id: stationName
                    font.pixelSize: parent.height/1.3
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width / 20
                    text: BusModel.StationName
                }
            }
        }
        Rectangle{
            id: stationAdressWrap
            width: parent.width
            height: parent.height / 30
            color: parent.color
            anchors.top: stationTitle.bottom
            Text {
                id: stationAddressName
                text: BusModel.StationAddress
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: parent.width/20
                font.pixelSize: parent.height*0.5
            }
        }
        Rectangle{
            id: listOptionWrap
            anchors.top: stationAdressWrap.bottom
            width: parent.width * 0.9
            height: parent.height/20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: height/3
            color: "#f7f7f7"
            Rectangle{
                id: routeListWrap
                height: parent.height
                width: parent.width / 2
                color: v_routeListEnable ? "#00897b" : parent.color
                Text {
                    id: routeListName
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 3
                    color: v_routeListEnable ? "white" : "black"
                    text: qsTr("Danh sách tuyến")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_routeListEnable = true
                    }
                }
            }
            Rectangle{
                id: vehicleListWrap
                height: parent.height
                width: parent.width / 2
                anchors.left: routeListWrap.right
                color: v_routeListEnable ? parent.color : "#00897b"
                Text {
                    id: vehicleListName
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 3
                    color: v_routeListEnable ? "black" : "white"
                    text: qsTr("Danh sách xe")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_routeListEnable = false
                    }
                }
            }
        }

        ListModel {
            id: station1
            ListElement {
                stationRouteName: "Tuyến số 19"
                mainStationsName: "Bến Xe Buýt Sài Gòn - Khu Chế Xuất Linh Trung - Đại Học Quốc Gia"
            }
            ListElement {
                stationRouteName: "Tuyến số 53"
                mainStationsName: "Lê Hồng Phong - Đại học Quốc gia"
            }
            ListElement {
                stationRouteName: "Tuyến số 45"
                mainStationsName: "Bến xe buýt Quận 8 - Bến Thành - Bến xe Miền Đông"
            }
            ListElement {
                stationRouteName: "Tuyến số 46"
                mainStationsName: "Bến xe buýt Quận 8 - Bến Thành - Bến xe Miền Đông"
            }
            ListElement {
                stationRouteName: "Tuyến số 47"
                mainStationsName: "Bến xe buýt Quận 8 - Bến Thành - Bến xe Miền Đông"
            }
            ListElement {
                stationRouteName: "Tuyến số 48"
                mainStationsName: "Bến xe buýt Quận 8 - Bến Thành - Bến xe Miền Đông"
            }
        }

        Rectangle{
            id: detailRouteListWrap
            width: parent.width * 0.9
            height: parent.height - stationTitle.height - listOptionWrap.height * 2.8
            anchors.top: listOptionWrap.bottom
            anchors.topMargin: listOptionWrap.height/3
            anchors.horizontalCenter: parent.horizontalCenter
            visible: v_routeListEnable

            ListView{
                anchors.fill: parent

                model: BusModel.NoCurrentBusRoute > 0 ? (BusModel.NoCurrentBusRoute < 999999 ? BusModel.NoCurrentBusRoute : 0) : 0
                spacing: listOptionWrap.height
                clip: true

                delegate:
                    Rectangle{
                    id: routewrap
                    width: detailRouteListWrap.width
                    height: route.height
                    color: "transparent"
                    StationRouteItem{
                        id: route
                        width: parent.width
                        p_referHeight: listOptionWrap.height
                        v_index: index
                        v_stationRouteName: "Tuyến số " + BusModel.BusRouteList[index].BusRouteName // stationRouteName
                        v_mainStationsName: BusModel.BusRouteList[index].BusMainRouteStation // mainStationsName
                    }
                }
            }
        }

        Rectangle{
            id: detailItemListWrap
            width: parent.width * 0.9
            height: parent.height - stationTitle.height - listOptionWrap.height * 2.8
            anchors.top: listOptionWrap.bottom
            anchors.topMargin: listOptionWrap.height/3
            anchors.horizontalCenter: parent.horizontalCenter
            visible: !v_routeListEnable

            ListView{
                anchors.fill: parent

                model: BusModel.BusItemList.length > 0 ? (BusModel.NoCurrentBusItem < 100 ? BusModel.NoCurrentBusItem : 0) : 0
                spacing: listOptionWrap.height
                clip: true

                delegate:
                    Rectangle{
                    width: parent.width
                    height: listOptionWrap.height * 0.8
                    StationVehicleItem2{
                        id: vbus1
                        referHeight: listOptionWrap.height * 0.8
                        width: parent.width
                        v_busid: BusModel.BusItemList[index].BusId //model.BusId // busid
                        v_busSpeed: BusModel.BusItemList[index].Speed //model.Speed // busSpeed
                        v_arrivalTime: BusModel.BusItemList[index].TimeArrival// arrivalTime
                        v_busDistance: BusModel.BusItemList[index].Distance //model.Peoples // busDistance
                        v_Temperature: BusModel.BusItemList[index].Temperature
                        v_Huminity: BusModel.BusItemList[index].Huminity
                        v_Peoples: BusModel.BusItemList[index].Peoples
                        v_stationRouteName: "Tuyến số " + BusModel.BusItemList[index].BusRoute
                    }
                }
            }
        }

        Rectangle{
            id: routeListChoosingWrap
            width: parent.width * 0.9
            height: parent.height * 0.1
            color: "#10af7e"
            anchors.bottom: parent.bottom
            anchors.left: parent.Left
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: titleRouteListChoosing
                width: parent.width * 0.2
                height: parent.height
                color: "#10af7e"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    id: buttonText
                    anchors.centerIn: parent
                    text: qsTr("Chọn tuyến xe đi")
                    font.bold: true
                    font.pixelSize: 15
                    color: "white"
                }
            }

            Rectangle{
                id: routeListChooseListview
                width: parent.width * 0.8
                height: parent.height
                anchors.left: titleRouteListChoosing.right
                color: "#10af7e"

                ListView{
                    id: chooseListView
                    anchors.fill: parent
                    anchors.left: parent.left
                    model: BusModel.ChooseBusRouteList.length > 0 ? (BusModel.ChooseBusRouteList.length < 999999 ? BusModel.ChooseBusRouteList.length : 0) : 0
                    spacing: 10
                    clip: true
                    orientation: ListView.Horizontal

                    delegate:
                        Rectangle{
                        height: chooseListView.height  - 20
                        width: chooseListView.height * 3
                        color: "#10af7e"
                        ChooseBusRoute{
                            referHeight: chooseListView.height * 3
                            v_index: index
                            v_routename: "Tuyến số " + BusModel.ChooseBusRouteList[index].BusID
                            v_mainstations: BusModel.ChooseBusRouteList[index].BusRoute
                            v_choosen: BusModel.ChooseBusRouteList[index].IsChoosen
                            v_status: BusModel.ChooseBusRouteList[index].Status
                        }
                    }
                }
            }
        }
    }

}
