#include "busitem.h"

BusItem::BusItem(QObject *parent)
    : QObject{parent}
{

}

float BusItem::Temperature() const
{
    return m_Temperature;
}

void BusItem::setTemperature(float newTemperature)
{
    if (qFuzzyCompare(m_Temperature, newTemperature))
        return;
    m_Temperature = newTemperature;
    emit TemperatureChanged();
}

float BusItem::Huminity() const
{
    return m_Huminity;
}

void BusItem::setHuminity(float newHuminity)
{
    if (qFuzzyCompare(m_Huminity, newHuminity))
        return;
    m_Huminity = newHuminity;
    emit HuminityChanged();
}

float BusItem::Longitude() const
{
    return m_Longitude;
}

void BusItem::setLongitude(float newLongitude)
{
    if (qFuzzyCompare(m_Longitude, newLongitude))
        return;
    m_Longitude = newLongitude;
    emit LongitudeChanged();
}

float BusItem::Latitude() const
{
    return m_Latitude;
}

void BusItem::setLatitude(float newLatitude)
{
    if (qFuzzyCompare(m_Latitude, newLatitude))
        return;
    m_Latitude = newLatitude;
    emit LatitudeChanged();
}

float BusItem::Altitude() const
{
    return m_Altitude;
}

void BusItem::setAltitude(float newAltitude)
{
    if (qFuzzyCompare(m_Altitude, newAltitude))
        return;
    m_Altitude = newAltitude;
    emit AltitudeChanged();
}

float BusItem::Speed() const
{
    return m_Speed;
}

void BusItem::setSpeed(float newSpeed)
{
    if (qFuzzyCompare(m_Speed, newSpeed))
        return;
    m_Speed = newSpeed;
    emit SpeedChanged();
}

int BusItem::Peoples() const
{
    return m_Peoples;
}

void BusItem::setPeoples(int newPeoples)
{
    if (m_Peoples == newPeoples)
        return;
    m_Peoples = newPeoples;
    emit PeoplesChanged();
}

QString BusItem::BusId() const
{
    return m_BusId;
}

void BusItem::setBusId(const QString &newBusId)
{
    if (m_BusId == newBusId)
        return;
    m_BusId = newBusId;
    emit BusIdChanged();
}

QString BusItem::BusRoute() const
{
    return m_BusRoute;
}

void BusItem::setBusRoute(const QString &newBusRoute)
{
    if (m_BusRoute == newBusRoute)
        return;
    m_BusRoute = newBusRoute;
    emit BusRouteChanged();
}

qint64 BusItem::TimeStamp() const
{
    return m_TimeStamp;
}

void BusItem::setTimeStamp(qint64 newTimeStamp)
{
    if (m_TimeStamp == newTimeStamp)
        return;
    m_TimeStamp = newTimeStamp;
    emit TimeStampChanged();
}


QString BusItem::Distance() const
{
    return m_Distance;
}

void BusItem::setDistance(const QString &newDistance)
{
    if (m_Distance == newDistance)
        return;
    m_Distance = newDistance;
    emit DistanceChanged();
}

QString BusItem::MainStations() const
{
    return m_MainStations;
}

void BusItem::setMainStations(const QString &newMainStations)
{
    if (m_MainStations == newMainStations)
        return;
    m_MainStations = newMainStations;
    emit MainStationsChanged();
}

int BusItem::TimeArrival() const
{
    return m_TimeArrival;
}

void BusItem::setTimeArrival(int newTimeArrival)
{
    if (m_TimeArrival == newTimeArrival)
        return;
    m_TimeArrival = newTimeArrival;
    emit TimeArrivalChanged();
}
