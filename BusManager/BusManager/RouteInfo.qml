import QtQuick 2.15

Item {
    property int v_routeNumber: 53
    property bool v_forwardDirectionEnable: true
    property int v_infoOption: 1

    Rectangle{
        id: routeInfoWrap
        height: parent.height
        width: parent.width / 4
        color: "white"
        Rectangle{
            id: routeTitle
            width: parent.width
            height: parent.height/13
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
                        main_routeInfo.visible = false
                        main_listRoute.visible = true
                        mapview1.visible = false
                        mapview2.visible = false
                    }
                }
            }
            Rectangle{
                id: routeNameWrap
                anchors.left: backIconWrap.right
                width: parent.width - backIconWrap.width
                height: parent.height
                Text {
                    id: routeName
                    font.pixelSize: parent.height/2
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: parent.width / 10
                    text: qsTr("Tuyến số ") + v_routeNumber
                }
            }
        }
        Rectangle{
            id: directionOptionWrap
            anchors.top: routeTitle.bottom
            width: parent.width * 0.9
            height: parent.height/20
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#f7f7f7"
            Rectangle{
                id: forwardDirection
                height: parent.height
                width: parent.width / 2
                color: v_forwardDirectionEnable ? "#00897b" : parent.color
                Text {
                    id: forwardName
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 3
                    color: v_forwardDirectionEnable ? "white" : "black"
                    text: qsTr("Xem lượt đi")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_forwardDirectionEnable = true
                    }
                }
            }
            Rectangle{
                id: backwardDirection
                height: parent.height
                width: parent.width / 2
                anchors.left: forwardDirection.right
                color: v_forwardDirectionEnable ? parent.color : "#00897b"
                Text {
                    id: backwardName
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 3
                    color: v_forwardDirectionEnable ? "black" : "white"
                    text: qsTr("Xem lượt về")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_forwardDirectionEnable = false
                    }
                }
            }
        }
        Rectangle{
            id: infoOptionsWrap
            anchors.top: directionOptionWrap.bottom
            width: parent.width * 0.9
            height: parent.height/20
            anchors.topMargin: height / 3
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#f7f7f7"
            Rectangle{
                id: infoOption_1
                height: parent.height / 1.5
                width: parent.width/4.3
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: parent.width/26
                color: v_infoOption == 1 ? "white" : parent.color
                radius: 7
                Text {
                    id: optionName1
                    anchors.centerIn: parent
                    font.pixelSize: parent.height / 2.3
                    color: v_infoOption == 1 ? "#00897b" : "black"
                    text: qsTr("Biểu đồ giờ")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_infoOption = 1
                    }
                }
            }
            Rectangle{
                id: infoOption_2
                height: parent.height / 1.5
                width: infoOption_1.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: infoOption_1.right
                color: v_infoOption == 2 ? "white" : parent.color
                radius: infoOption_1.radius
                Text {
                    id: optionName2
                    anchors.centerIn: parent
                    font.pixelSize: optionName1.font.pixelSize
                    color: v_infoOption == 2 ? "#00897b" : "black"
                    text: qsTr("Trạm dừng")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_infoOption = 2
                    }
                }
            }
            Rectangle{
                id: infoOption_3
                height: parent.height / 1.5
                width: infoOption_1.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: infoOption_2.right
                color: v_infoOption == 3 ? "white" : parent.color
                radius: infoOption_1.radius
                Text {
                    id: optionName3
                    anchors.centerIn: parent
                    font.pixelSize: optionName1.font.pixelSize
                    color: v_infoOption == 3 ? "#00897b" : "black"
                    text: qsTr("Thông tin")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_infoOption = 3
                    }
                }
            }
            Rectangle{
                id: infoOption_4
                height: parent.height / 1.5
                width: infoOption_1.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: infoOption_3.right
                color: v_infoOption == 4 ? "white" : parent.color
                radius: infoOption_1.radius
                Text {
                    id: optionName4
                    anchors.centerIn: parent
                    font.pixelSize: optionName1.font.pixelSize
                    color: v_infoOption == 4 ? "#00897b" : "black"
                    text: qsTr("Đánh giá")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_infoOption = 4
                    }
                }
            }
        }
        Rectangle{
            id: detailInfoWrap
            width: parent.width * 0.9
            height: parent.height - routeTitle.height - directionOptionWrap.height - infoOptionsWrap.height - infoOptionsWrap.height
            anchors.top: infoOptionsWrap.bottom
            anchors.topMargin: infoOptionsWrap.height/3
            anchors.horizontalCenter: parent.horizontalCenter
            Loader {
                id: detailInfoLoader
                anchors.fill: parent
                source: "BusTimeline.qml"
            }
        }
    }

}
