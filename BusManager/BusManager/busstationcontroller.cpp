#include "busstationcontroller.h"

BusStationController::BusStationController(QObject *parent)
    : QObject{parent}
{
    m_NoCurrentBusRoute = 0;

    m_BusRouteList.clear();

    connect(&mCheckStatusTimer, SIGNAL(timeout()), this, SLOT(checkStatus()));
    mCheckStatusTimer.start(DURATION_CHECK_BUS_STATUS);

    connect(&mUpdateBusInfoTimer, SIGNAL(timeout()), this, SLOT(updateStationInfo()));
    mUpdateBusInfoTimer.start(1000);

    m_ChooseBusRouteList.clear();

    ChooseBusRoute *tmp;
    tmp = new ChooseBusRoute();
    tmp->setBusID("53");
    tmp->setBusRoute("Lê Hồng Phong - Đại học Quốc gia");
    tmp->setIsChoosen(0);
    tmp->setStatus(0);
    addChooseBusRoute(tmp);
}

void BusStationController::setStatus(int index, int status)
{
    if(index >= 0 && index < m_ChooseBusRouteList.length()){
        m_ChooseBusRouteList[index]->setStatus(status);
        qDebug() << "---- Set " << index << " = " << status << " status success";
        qDebug() << " result: " << m_ChooseBusRouteList[index]->Status();

        emit ChooseBusRouteListChanged();
    }
}

void BusStationController::addBusItem(BusItem *item)
{
    updateBusRouteList(item);
    updateBusItemList(item);

    qDebug() << "========= " << m_BusItemList.length();
    qDebug() << "========= " << m_BusRouteList.length();

    delete item;
}

void BusStationController::addChooseBusRoute(ChooseBusRoute *item)
{
    for(int i = 0; i < m_ChooseBusRouteList.length(); i++){
        if(m_ChooseBusRouteList[i]->BusID() == item->BusID()){
            return;
        }
    }

    m_ChooseBusRouteList.append(item);

    qDebug() << "=== m_ChooseBusRouteList.length = " << m_ChooseBusRouteList.length();

    emit ChooseBusRouteListChanged();
}

QString BusStationController::StationName() const
{
    return m_StationName;
}

void BusStationController::setStationName(const QString &newStationName)
{
    if (m_StationName == newStationName)
        return;
    m_StationName = newStationName;
    emit StationNameChanged();
}

QString BusStationController::StationAddress() const
{
    return m_StationAddress;
}

void BusStationController::setStationAddress(const QString &newStationAddress)
{
    if (m_StationAddress == newStationAddress)
        return;
    m_StationAddress = newStationAddress;
    emit StationAddressChanged();
}

int BusStationController::NoCurrentBusRoute() const
{
    return m_NoCurrentBusRoute;
}

void BusStationController::setNoCurrentBusRoute(int newNoCurrentBusRoute)
{
    if (m_NoCurrentBusRoute == newNoCurrentBusRoute)
        return;
    m_NoCurrentBusRoute = newNoCurrentBusRoute;
    emit NoCurrentBusRouteChanged();
}

QList<BusRoute *> BusStationController::BusRouteList() const
{
    return m_BusRouteList;
}

void BusStationController::updateBus(BusItem *item)
{
    addBusItem(item);
    qDebug() << "---------- Add bus item" << m_NoCurrentBusRoute;
}

void BusStationController::checkStatus()
{
    qDebug() << "+++++ check status";
    qint64 currTimestamp = QDateTime::currentMSecsSinceEpoch();
    for(int i = 0; i < m_BusRouteList.length(); i++){
        for(int j = 0; j < m_BusRouteList[i]->BusItemList().length(); j++){
            if(currTimestamp - m_BusRouteList[i]->BusItemList()[j]->TimeStamp() > DURATION_TO_REMOVE_BUS_FROM_LIST){
                m_BusRouteList[i]->removeBusAt(j);
                if(m_BusRouteList[i]->NoBusItem() == 0){
                    delete m_BusRouteList[i];
                    m_BusRouteList.removeAt(i);
                    m_NoCurrentBusRoute--;
                    i--;
                    break;
                }
            }
        }
    }
    emit NoCurrentBusRouteChanged();
    emit BusRouteListChanged();

    for(int i = 0; i < m_BusItemList.length(); i++){
        if(currTimestamp - m_BusItemList[i]->TimeStamp() > DURATION_TO_REMOVE_BUS_FROM_LIST){
            delete m_BusItemList[i];
            m_BusItemList.removeAt(i);
            m_NoCurrentBusItem--;
            i--;
        }
    }
    emit NoCurrentBusItemChanged();
    emit BusItemListChanged();
}

void BusStationController::updateStationInfo()
{
    qDebug() << "update bus info";
    m_StationAddress = BUS_STATION_ADDRESS;
    m_StationName = BUS_STATION_NAME;

    emit StationAddressChanged();
    emit StationNameChanged();

    mUpdateBusInfoTimer.stop();
}

void BusStationController::handleResponse(int id)
{
    qDebug() << "Handle responseddddddddddddddddddddddddddddddddddddddddddddddd";
    setStatus(0, 0);
}

void BusStationController::updateBusRouteList(BusItem *item)
{
    // Update bus route list
    for(int i = 0; i < m_BusRouteList.length(); i++){
        if(m_BusRouteList[i]->BusRouteName() == item->BusRoute()){
            m_BusRouteList[i]->addBusItem(item);
            return;
        }
    }

    BusRoute *tmpRoute = new BusRoute();
    tmpRoute->setBusRouteName(item->BusRoute());
    tmpRoute->setBusMainRouteStation(item->MainStations());
    tmpRoute->addBusItem(item);

    m_BusRouteList.append(tmpRoute);
    m_NoCurrentBusRoute++;

    emit NoCurrentBusRouteChanged();
    emit BusRouteListChanged();
}

void BusStationController::updateBusItemList(BusItem *item)
{
    for(int i = 0; i < m_BusItemList.length(); i++){
        if(m_BusItemList[i]->BusId() == item->BusId()){
            m_BusItemList[i]->setTemperature(item->Temperature());
            m_BusItemList[i]->setHuminity(item->Huminity());
            m_BusItemList[i]->setLongitude(item->Longitude());
            m_BusItemList[i]->setLatitude(item->Latitude());
            m_BusItemList[i]->setAltitude(item->Altitude());
            m_BusItemList[i]->setSpeed(item->Speed());
            m_BusItemList[i]->setPeoples(item->Peoples());
            m_BusItemList[i]->setTimeStamp(item->TimeStamp());
            m_BusItemList[i]->setTimeArrival(item->TimeArrival());
            m_BusItemList[i]->setDistance(item->Distance());
            return;
        }
    }

    BusItem *tmpItem = new BusItem();
    tmpItem->setTemperature(item->Temperature());
    tmpItem->setHuminity(item->Huminity());
    tmpItem->setLongitude(item->Longitude());
    tmpItem->setLatitude(item->Latitude());
    tmpItem->setAltitude(item->Altitude());
    tmpItem->setSpeed(item->Speed());
    tmpItem->setPeoples(item->Peoples());
    tmpItem->setBusId(item->BusId());
    tmpItem->setBusRoute(item->BusRoute());
    tmpItem->setTimeStamp(item->TimeStamp());
    tmpItem->setTimeArrival(item->TimeArrival());
    tmpItem->setDistance(item->Distance());

    m_BusItemList.append(tmpItem);
    m_NoCurrentBusItem++;

    emit BusItemListChanged();
    emit NoCurrentBusItemChanged();
}

QList<BusItem *> BusStationController::BusItemList() const
{
    return m_BusItemList;
}

int BusStationController::NoCurrentBusItem() const
{
    return m_NoCurrentBusItem;
}

void BusStationController::setNoCurrentBusItem(int newNoCurrentBusItem)
{
    if (m_NoCurrentBusItem == newNoCurrentBusItem)
        return;
    m_NoCurrentBusItem = newNoCurrentBusItem;
    emit NoCurrentBusItemChanged();
}

QList<ChooseBusRoute *> BusStationController::ChooseBusRouteList() const
{
    return m_ChooseBusRouteList;
}
