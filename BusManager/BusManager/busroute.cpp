#include "busroute.h"

BusRoute::BusRoute(QObject *parent)
    : QObject{parent}
{
    m_NoBusItem = 0;
    m_BusItemList.clear();
}

void BusRoute::addBusItem(BusItem *item)
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
    m_NoBusItem++;

    emit BusItemListChanged();
    emit NoBusItemChanged();
}

void BusRoute::removeBusAt(int i)
{
    m_BusItemList.removeAt(i);
    m_NoBusItem--;

    emit NoBusItemChanged();
    emit BusItemListChanged();
}

QList<BusItem *> BusRoute::BusItemList() const
{
    return m_BusItemList;
}

int BusRoute::NoBusItem() const
{
    return m_NoBusItem;
}

void BusRoute::setNoBusItem(int newNoBusItem)
{
    if (m_NoBusItem == newNoBusItem)
        return;
    m_NoBusItem = newNoBusItem;
    emit NoBusItemChanged();
}

QString BusRoute::BusRouteName() const
{
    return m_BusRouteName;
}

void BusRoute::setBusRouteName(const QString &newBusRouteName)
{
    if (m_BusRouteName == newBusRouteName)
        return;
    m_BusRouteName = newBusRouteName;
    emit BusRouteNameChanged();
}

QString BusRoute::BusMainRouteStation() const
{
    return m_BusMainRouteStation;
}

void BusRoute::setBusMainRouteStation(const QString &newBusMainRouteStation)
{
    if (m_BusMainRouteStation == newBusMainRouteStation)
        return;
    m_BusMainRouteStation = newBusMainRouteStation;
    emit BusMainRouteStationChanged();
}
