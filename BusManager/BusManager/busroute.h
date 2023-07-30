#ifndef BUSROUTE_H
#define BUSROUTE_H

#include <QObject>
#include "busitem.h"

class BusRoute : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<BusItem *> BusItemList READ BusItemList NOTIFY BusItemListChanged)
    Q_PROPERTY(int NoBusItem READ NoBusItem WRITE setNoBusItem NOTIFY NoBusItemChanged)
    Q_PROPERTY(QString BusRouteName READ BusRouteName WRITE setBusRouteName NOTIFY BusRouteNameChanged)
    Q_PROPERTY(QString BusMainRouteStation READ BusMainRouteStation WRITE setBusMainRouteStation NOTIFY BusMainRouteStationChanged)

public:
    explicit BusRoute(QObject *parent = nullptr);

    void addBusItem(BusItem *item);
    void removeBusAt(int i);

    QList<BusItem *> BusItemList() const;

    int NoBusItem() const;
    void setNoBusItem(int newNoBusItem);

    QString BusRouteName() const;
    void setBusRouteName(const QString &newBusRouteName);

    QString BusMainRouteStation() const;
    void setBusMainRouteStation(const QString &newBusMainRouteStation);

signals:

    void BusItemListChanged();
    void NoBusItemChanged();

    void BusRouteNameChanged();

    void BusMainRouteStationChanged();

private:
    QList<BusItem *> m_BusItemList;
    int m_NoBusItem;
    QString m_BusRouteName;
    QString m_BusMainRouteStation;
};

#endif // BUSROUTE_H
