#ifndef BUSSTATIONCONTROLLER_H
#define BUSSTATIONCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include "busroute.h"
#include "config.h"
#include "choosebusroute.h"

class BusStationController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString StationName READ StationName WRITE setStationName NOTIFY StationNameChanged)
    Q_PROPERTY(QString StationAddress READ StationAddress WRITE setStationAddress NOTIFY StationAddressChanged)
    Q_PROPERTY(int NoCurrentBusRoute READ NoCurrentBusRoute WRITE setNoCurrentBusRoute NOTIFY NoCurrentBusRouteChanged)
    Q_PROPERTY(int NoCurrentBusItem READ NoCurrentBusItem WRITE setNoCurrentBusItem NOTIFY NoCurrentBusItemChanged)
    Q_PROPERTY(QList<BusRoute *> BusRouteList READ BusRouteList NOTIFY BusRouteListChanged)
    Q_PROPERTY(QList<BusItem *> BusItemList READ BusItemList NOTIFY BusItemListChanged)

    Q_PROPERTY(QList<ChooseBusRoute *> ChooseBusRouteList READ ChooseBusRouteList NOTIFY ChooseBusRouteListChanged)

public:
    explicit BusStationController(QObject *parent = nullptr);

    Q_INVOKABLE void setStatus(int index, int status);

    void addBusItem(BusItem *item);

    void addChooseBusRoute(ChooseBusRoute *item);

    QString StationName() const;
    void setStationName(const QString &newStationName);

    QString StationAddress() const;
    void setStationAddress(const QString &newStationAddress);

    int NoCurrentBusRoute() const;
    void setNoCurrentBusRoute(int newNoCurrentBusRoute);

    QList<BusRoute *> BusRouteList() const;

    QList<BusItem *> BusItemList() const;

    int NoCurrentBusItem() const;
    void setNoCurrentBusItem(int newNoCurrentBusItem);

    QList<ChooseBusRoute *> ChooseBusRouteList() const;

public slots:
    void updateBus(BusItem *item);
    void checkStatus();
    void updateStationInfo();

    void handleResponse(int id);

signals:

    void StationNameChanged();
    void StationAddressChanged();
    void NoCurrentBusRouteChanged();
    void BusRouteListChanged();

    void BusItemListChanged();

    void NoCurrentBusItemChanged();

    void ChooseBusRouteListChanged();

private:
    void updateBusRouteList(BusItem *item);
    void updateBusItemList(BusItem *item);

private:
    QString m_StationName;
    QString m_StationAddress;
    int m_NoCurrentBusRoute;
    QList<BusRoute *> m_BusRouteList;

    QTimer mCheckStatusTimer;
    QTimer mUpdateBusInfoTimer;
    QList<BusItem *> m_BusItemList;
    int m_NoCurrentBusItem;


    QList<ChooseBusRoute *> m_ChooseBusRouteList;

};

#endif // BUSSTATIONCONTROLLER_H
