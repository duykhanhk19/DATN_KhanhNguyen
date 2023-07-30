import QtQuick 2.15

Item {
    Rectangle{
        anchors.fill: parent
        color: "blue"

        Rectangle{
            id: dateInfoWrap
            width: parent.width
            height: parent.height/15
            color:  "yellow"//parent.color
            Image {
                id: nextIcon
                source: "./Images/moveNextIcon.svg"
                height: parent.height*0.6
                width: height
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
            Rectangle{
                id: detailDayInfo
                width: detailDayText.width*1.3
                height: parent.height
                color: parent.color
                anchors.right: nextIcon.left
                Text {
                    id: detailDayText
                    text: qsTr("HÔM NAY")
                    anchors.centerIn: parent
                    font.pixelSize: parent.height*0.4
                }
            }
            Image {
                id: previousIcon
                source: "./Images/movePreviousIcon.svg"
                height: parent.height*0.6
                width: height
                anchors.right: detailDayInfo.left
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
