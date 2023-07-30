import QtQuick 2.15

Item {

    property bool v_searchOption: true

    Rectangle{
        id: optionsSearchWrap
        height: parent.height
        width: parent.width / 4
        color: "white"

        Rectangle{
            id: searchOptionsWrap
            anchors.top: optionsSearchWrap.top
            width: parent.width * 0.9
            height: parent.height/20 * 1.2
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#f7f7f7"
            Rectangle{
                id: routeSearchWrap
                height: parent.height
                width: parent.width / 2
                Image {
                    id: searchIcon
                    height: parent.height * 0.5
                    width: height
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width / 8
                    anchors.verticalCenter: parent.verticalCenter
                    source: "/Images/searchIcon.png"
                }
                Text {
                    id: routeSearchName
                    anchors.left: searchIcon.right
                    anchors.leftMargin: parent.width / 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: parent.height / 3
                    color: v_searchOption ? "#00897b" : "black"
                    text: qsTr("TRA CỨU")
                }
                Rectangle{
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: parent.height * 0.05
                    color: v_searchOption ? "#00897b" : "#f7f7f7"
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_searchOption = true
                    }
                }
            }


            Rectangle{
                id: locationSearchWrap
                height: parent.height
                width: parent.width / 2
                anchors.left: routeSearchWrap.right
                Image {
                    id: mapIcon
                    height: parent.height * 0.5
                    width: height
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width / 8
                    anchors.verticalCenter: parent.verticalCenter
                    source: "/Images/mapIcon.png"
                }
                Text {
                    id: locationSearchName
                    anchors.left: mapIcon.right
                    anchors.leftMargin: parent.width / 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: parent.height / 3
                    color: v_searchOption ? "black" : "#00897b"
                    text: qsTr("TÌM ĐƯỜNG")
                }
                Rectangle{
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: parent.height * 0.05
                    color: v_searchOption ? "#f7f7f7" : "#00897b"
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        v_searchOption = false
                    }
                }
            }
        }

        Rectangle{
            id: stationInfoWrap
            width: parent.width * 0.7
            height: parent.height / 20
            anchors.top: searchOptionsWrap.bottom
            anchors.topMargin: height / 5
            color: "#00897b"
            anchors.horizontalCenter: parent.horizontalCenter
            radius: height/4
            Text {
                text: qsTr("Thông tin trạm")
                anchors.centerIn: parent
                font.pixelSize: parent.height / 2
                color: "white"
                font.bold: true
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    main_stationInfo.visible = true
                    main_listRoute.visible = false
                    main_map.visible = false
                }
            }
        }

        Rectangle{
            id: searchBoxWrap
            width: parent.width * 0.9
            height: parent.height / 20
            anchors.top: stationInfoWrap.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: height / 5
            radius: height / 6
            color: "#f7f7f7"

            TextEdit {
                id: searchInput
                anchors.fill: parent
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.05
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: TextEdit.AlignVCenter
                leftPadding:  width * 0.05
                font.pixelSize: height * 0.4
                color: "#8b8b8b"

                property string placeholderText: "Tìm chuyến xe"

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width * 0.05
                    anchors.verticalCenter: parent.verticalCenter
                    text: searchInput.placeholderText
                    font.pixelSize: searchInput.height * 0.4
                    color: "#8b8b8b"
                    visible: !searchInput.text & (!searchInput.contentWidth)
                }
            }
        }

        Rectangle{
            id: listRoutesWrap
            anchors.top: searchBoxWrap.bottom
            anchors.topMargin: searchBoxWrap.height * 0.2
            width: parent.width
            height: parent.height - searchBoxWrap.height - searchOptionsWrap.height

            ListView{
                id: routeListView
                anchors.fill: parent
                anchors.top: parent.top
                model: 10
                spacing: searchBoxWrap.height * 0.3
                clip: true
                delegate:
                    ListRouteItem{
                        width: listRoutesWrap.width
                        referHeight: searchBoxWrap.height * 2.4
                    }
            }
        }
    }

}
