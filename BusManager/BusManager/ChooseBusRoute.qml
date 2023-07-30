import QtQuick 2.15

Item {
    property int referHeight: 50
    property string v_routename: "Tuyến số 53"
    property string v_mainstations: "Bến xe buýt Quận 8 - Bến Thành - Bến xe Miền Đông"
    property int v_status: 0
    property int v_choosen: 1
    property int v_index: 0

    Rectangle{
        width: referHeight
        height: referHeight * 0.45
        anchors.left: parent.left
        color: "#8b8b8b"
        opacity: v_status == 1 ? 1 : 0.8
        radius: 10
        border.color: "black"
//        border.width: v_status == 1 ? 2 : 0
        Text {
            id: routename
            text: v_routename
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: referHeight/20
            font.pixelSize: 14
            color: "white"
            font.bold: true
        }
        Text {
            id: mainroutes
            anchors.top: routename.bottom
            anchors.left: parent.left
            anchors.margins: referHeight/20
            text: v_mainstations
            width: parent.width
            wrapMode: Text.WordWrap
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
//                v_choosen = !v_choosen
//                BusModel.setStatus(index, v_choosen);
                if(v_status == 0){
                    Lora.sendLora("53")
//                    v_choosen = 1
                    BusModel.setStatus(v_index, 1);
                    console.log("11111111")
                }
                else{
//                    v_choosen = 0
                    BusModel.setStatus(v_index, 0);
                    console.log("0000000")
                }
            }
//            onEntered: {
//                v_status = 1
//            }
//            onExited: {
//                v_status = 0
//            }
        }
    }
}
