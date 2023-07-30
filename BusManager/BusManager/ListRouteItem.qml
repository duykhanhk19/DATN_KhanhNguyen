import QtQuick 2.15

Item {
    property int referHeight: value
    height: routeInfo.height

    Rectangle{
        id: routeInfo
        width: parent.width*0.9
        height: referHeight
        anchors.horizontalCenter: parent.horizontalCenter
        radius: width * 0.03
        color: "#f7f7f7"
        Rectangle{
            id: busIconWrap
            height: parent.height
            width: parent.width / 5
            color: "transparent"
            Image {
                id: busIcon
                width: parent.width * 0.6
                height: width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: height / 3
                source: "/Images/busIcon2.svg"
            }
        }
        Rectangle{
            id: routeInfoWrap
            width: parent.width * 4/5
            height: routenameWrap.height + mainRoutesWrap.height + otherInfoWrap.height
            anchors.left: busIconWrap.right
            color: "transparent"
            Rectangle{
                id: routenameWrap
                anchors.top: parent.top
                width: parent.width
                height: searchBoxWrap.height * 0.7
                color: "transparent"
                Text {
                    id: routeName
                    font.pixelSize: parent.height * 0.7
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    color: "#34b67a"
                    text: qsTr("Tuyến số 53")
                }
            }
            Rectangle{
                id: mainRoutesWrap
                width: parent.width
                height: mainRoutes.height
                anchors.top: routenameWrap.bottom
                color: "transparent"
                Text {
                    id: mainRoutes
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: routenameWrap.height * 0.5
                    text: qsTr("Vinhomes Grand Park - Bến xe buýt Sài Gòn")
                    wrapMode: Text.WordWrap
                }
            }
            Rectangle{
                id: otherInfoWrap
                width: parent.width
                height: routenameWrap.height
                anchors.top: mainRoutesWrap.bottom
                color: "transparent"
                Text {
                    id: timeWorking
                    anchors.left: parent.left
                    font.pixelSize: routenameWrap.height * 0.5
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("05:00 - 20:15")
                }
                Text {
                    id: price
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width / 20
                    font.pixelSize: routenameWrap.height * 0.5
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("5000 VND")
                }
            }
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            main_routeInfo.visible = true
            main_listRoute.visible = false
            mapview1.visible = true
            mapview2.visible = true
        }
    }
}
