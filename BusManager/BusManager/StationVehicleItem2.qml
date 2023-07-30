import QtQuick 2.15

Item {
    property int referHeight: 50
    property string v_stationRouteName: "Tuyến số 19"
    property string v_busid: "51B-249.33"
    property int v_arrivalTime: 200
    property int v_busSpeed: 50
    property string v_busDistance: "23"
    property double v_Temperature: 0
    property double v_Huminity: 0
    property int v_Peoples: 0

    height: referHeight

    Rectangle{
        height: referHeight
        width: parent.width
        color: "#f7f7f7"
        Rectangle{
            id: busIdWrap
            width: parent.width / 6.9
            height: parent.height * 1.2
            anchors.left: parent.left
            anchors.leftMargin: width / 7
            anchors.verticalCenter: parent.verticalCenter
            color: "#00897b"
            radius: 5
            Text {
                id: busRoute
                text: v_stationRouteName
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.1
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: referHeight / 2.6
                color: "white"
            }
            Text {
                id: busId
                text: v_busid
                anchors.top: busRoute.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: referHeight / 2.6
                color: "white"
            }
        }
        Rectangle{
            id: arrivalTimeWrap
            width: busIdWrap.width
            height: busIdWrap.height
            anchors.left: busIdWrap.right
            anchors.leftMargin: width / 3
            anchors.verticalCenter: parent.verticalCenter
            color: "transparent"
            radius: 5
            Image {
                id: clockIcon
                height: referHeight * 0.4
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: referHeight / 10
                source: "./Images/clockIcon.svg"
            }
            Text {
                id: arrivalTime
                text: v_arrivalTime + qsTr(" phút")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: clockIcon.right
                anchors.leftMargin: referHeight / 8
                font.pixelSize: referHeight / 2.6
            }
        }
        Rectangle{
            id: busSpeedWrap
            width: busIdWrap.width
            height: busIdWrap.height
            anchors.left: arrivalTimeWrap.right
            anchors.leftMargin: width / 16
            anchors.verticalCenter: parent.verticalCenter
            color: arrivalTimeWrap.color
            radius: 5
            Image {
                id: speedIcon
                height: referHeight * 0.4
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: referHeight / 10
                source: "./Images/speedIcon.svg"
            }
            Text {
                id: busSpeed
                text: v_busSpeed + qsTr(" km/h")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: speedIcon.right
                anchors.leftMargin: referHeight / 8
                font.pixelSize: referHeight / 2.6
            }
        }
        Rectangle{
            id: busDistanceWrap
            width: busIdWrap.width
            height: busIdWrap.height
            anchors.left: busSpeedWrap.right
            anchors.leftMargin: width / 16
            anchors.verticalCenter: parent.verticalCenter
            color: arrivalTimeWrap.color
            radius: 5
            Image {
                id: distanceIcon
                height: referHeight * 0.4
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: referHeight / 10
                source: "./Images/distanceIcon.svg"
            }
            Text {
                id: busDistance
                text: v_busDistance + " km"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: distanceIcon.right
                anchors.leftMargin: referHeight / 8
                font.pixelSize: referHeight / 2.6

                onTextChanged: {
                    console.log(v_busDistance)
                }
            }
        }
        Rectangle{
            id: busPeopleWrap
            width: busIdWrap.width
            height: busIdWrap.height
            anchors.left: busDistanceWrap.right
            anchors.leftMargin: width / 16
            anchors.verticalCenter: parent.verticalCenter
            color: arrivalTimeWrap.color
            radius: 5
            Image {
                id: peopleIcon
                height: referHeight * 0.6
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: referHeight / 10
                source: "./Images/peopleIcon.png"
            }
            Text {
                id: busPeople
                text: v_Peoples + qsTr(" peoples")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: peopleIcon.right
                anchors.leftMargin: referHeight / 8
                font.pixelSize: referHeight / 2.6
            }
        }
        Rectangle{
            id: busTemperatureWrap
            width: busIdWrap.width
            height: busIdWrap.height
            anchors.left: busPeopleWrap.right
            anchors.leftMargin: width / 16
            anchors.verticalCenter: parent.verticalCenter
            color: arrivalTimeWrap.color
            radius: 5
            Image {
                id: temperatureIcon
                height: referHeight * 0.6
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: referHeight / 10
                source: "./Images/temperatureIcon.png"
            }
            Text {
                id: busTemperature
                text: Math.round(v_Temperature * 100)/100 + qsTr(" °C")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: temperatureIcon.right
                anchors.leftMargin: referHeight / 8
                font.pixelSize: referHeight / 2.6
            }
            Text {
                id: busTemperature1
                text: Math.round(v_Huminity * 100)/100 + qsTr(" %")
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: referHeight
                font.pixelSize: referHeight / 2.6
            }
        }
    }
}
