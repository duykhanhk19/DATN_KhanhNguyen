#include "choosebusroute.h"

ChooseBusRoute::ChooseBusRoute(QObject *parent)
    : QObject{parent}
{

}

QString ChooseBusRoute::BusID() const
{
    return m_BusID;
}

void ChooseBusRoute::setBusID(const QString &newBusID)
{
    if (m_BusID == newBusID)
        return;
    m_BusID = newBusID;
    emit BusIDChanged();
}

QString ChooseBusRoute::BusRoute() const
{
    return m_BusRoute;
}

void ChooseBusRoute::setBusRoute(const QString &newBusRoute)
{
    if (m_BusRoute == newBusRoute)
        return;
    m_BusRoute = newBusRoute;
    emit BusRouteChanged();
}

int ChooseBusRoute::Status() const
{
    return m_Status;
}

void ChooseBusRoute::setStatus(int newStatus)
{
    if (m_Status == newStatus)
        return;
    m_Status = newStatus;
    emit StatusChanged();
}

int ChooseBusRoute::IsChoosen() const
{
    return m_IsChoosen;
}

void ChooseBusRoute::setIsChoosen(int newIsChoosen)
{
    if (m_IsChoosen == newIsChoosen)
        return;
    m_IsChoosen = newIsChoosen;
    emit IsChoosenChanged();
}
