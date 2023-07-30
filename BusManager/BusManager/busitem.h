#ifndef BUSITEM_H
#define BUSITEM_H

#include <QObject>

class BusItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float Temperature READ Temperature WRITE setTemperature NOTIFY TemperatureChanged)
    Q_PROPERTY(float Huminity READ Huminity WRITE setHuminity NOTIFY HuminityChanged)
    Q_PROPERTY(float Longitude READ Longitude WRITE setLongitude NOTIFY LongitudeChanged)
    Q_PROPERTY(float Latitude READ Latitude WRITE setLatitude NOTIFY LatitudeChanged)
    Q_PROPERTY(float Altitude READ Altitude WRITE setAltitude NOTIFY AltitudeChanged)
    Q_PROPERTY(float Speed READ Speed WRITE setSpeed NOTIFY SpeedChanged)
    Q_PROPERTY(int Peoples READ Peoples WRITE setPeoples NOTIFY PeoplesChanged)
    Q_PROPERTY(qint64 TimeStamp READ TimeStamp WRITE setTimeStamp NOTIFY TimeStampChanged)
    Q_PROPERTY(QString Distance READ Distance WRITE setDistance NOTIFY DistanceChanged)
    Q_PROPERTY(int TimeArrival READ TimeArrival WRITE setTimeArrival NOTIFY TimeArrivalChanged)

    Q_PROPERTY(QString BusId READ BusId WRITE setBusId NOTIFY BusIdChanged)
    Q_PROPERTY(QString BusRoute READ BusRoute WRITE setBusRoute NOTIFY BusRouteChanged)
    Q_PROPERTY(QString MainStations READ MainStations WRITE setMainStations NOTIFY MainStationsChanged)

public:
    explicit BusItem(QObject *parent = nullptr);

    float Temperature() const;
    void setTemperature(float newTemperature);

    float Huminity() const;
    void setHuminity(float newHuminity);

    float Longitude() const;
    void setLongitude(float newLongitude);

    float Latitude() const;
    void setLatitude(float newLatitude);

    float Altitude() const;
    void setAltitude(float newAltitude);

    float Speed() const;
    void setSpeed(float newSpeed);

    int Peoples() const;
    void setPeoples(int newPeoples);

    QString BusId() const;
    void setBusId(const QString &newBusId);

    QString BusRoute() const;
    void setBusRoute(const QString &newBusRoute);

    qint64 TimeStamp() const;
    void setTimeStamp(qint64 newTimeStamp);

    QString Distance() const;
    void setDistance(const QString &newDistance);

    QString MainStations() const;
    void setMainStations(const QString &newMainStations);

    int TimeArrival() const;
    void setTimeArrival(int newTimeArrival);

signals:

    void TemperatureChanged();

    void HuminityChanged();

    void LongitudeChanged();

    void LatitudeChanged();

    void AltitudeChanged();

    void SpeedChanged();

    void PeoplesChanged();

    void BusIdChanged();

    void BusRouteChanged();

    void TimeStampChanged();

    void DistanceChanged();

    void MainStationsChanged();

    void TimeArrivalChanged();

private:
    float m_Temperature;
    float m_Huminity;
    float m_Longitude;
    float m_Latitude;
    float m_Altitude;
    float m_Speed;
    int m_Peoples;
    QString m_BusId;
    QString m_BusRoute;
    qint64 m_TimeStamp;
    QString m_Distance;
    QString m_MainStations;
    int m_TimeArrival;
};

#endif // BUSITEM_H
