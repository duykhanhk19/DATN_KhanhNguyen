import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
//import QtWebEngine 1.9

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Sieu cap bus manager")
    color: "gray"

    ListRoutes{
        id: main_listRoute
        anchors.fill: parent
        visible: false
    }

    RouteInfo{
        id: main_routeInfo
        anchors.fill: parent
        visible: false
    }

    StationInfo{
        id: main_stationInfo
        anchors.fill: parent
        visible: true
    }

//    WebEngineView {
//        id: main_webview
//        anchors.fill: parent
//        url: "https://map.busmap.vn/hcm"
//        visible: false
//    }

//    Rectangle{
//        id: backToHome
//        width: parent.width / 23
//        height: width
//        color: "red"
//        signal stopRequest()
//        //visible: main_webview.visible
//        MouseArea{
//            anchors.fill: parent
//            onClicked: {
//                console.log("=======================================-----------------------------------------------")
//                Lora.requestSend()
//            }
//        }
//    }
}
