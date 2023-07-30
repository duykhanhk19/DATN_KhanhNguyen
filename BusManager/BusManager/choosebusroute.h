#ifndef CHOOSEBUSROUTE_H
#define CHOOSEBUSROUTE_H

#include <QObject>

class ChooseBusRoute : public QObject
{
    Q_OBJECT
public:
    explicit ChooseBusRoute(QObject *parent = nullptr);

    Q_PROPERTY(QString BusID READ BusID WRITE setBusID NOTIFY BusIDChanged)
    Q_PROPERTY(QString BusRoute READ BusRoute WRITE setBusRoute NOTIFY BusRouteChanged)
    Q_PROPERTY(int Status READ Status WRITE setStatus NOTIFY StatusChanged)
    Q_PROPERTY(int IsChoosen READ IsChoosen WRITE setIsChoosen NOTIFY IsChoosenChanged)

    QString BusID() const;
    void setBusID(const QString &newBusID);

    QString BusRoute() const;
    void setBusRoute(const QString &newBusRoute);

    int Status() const;
    void setStatus(int newStatus);

    int IsChoosen() const;
    void setIsChoosen(int newIsChoosen);

signals:

    void BusIDChanged();
    void BusRouteChanged();

    void StatusChanged();

    void IsChoosenChanged();

private:
    QString m_BusID;
    QString m_BusRoute;
    int m_Status;
    int m_IsChoosen;
};

#endif // CHOOSEBUSROUTE_H
