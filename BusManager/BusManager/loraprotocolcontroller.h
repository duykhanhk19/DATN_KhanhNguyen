#ifndef LORAPROTOCOLCONTROLLER_H
#define LORAPROTOCOLCONTROLLER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>
#include <stdint.h>
#include <QtMath>
#include <QTimer>
#include <QThread>
#include "busitem.h"
#include "config.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>


struct Header {
    unsigned int seq;
    unsigned int bus_id;
};

struct LoRaData{
    uint8_t temperature;
    uint8_t huminity;
    uint8_t peoples;
    double longitude;
    double latitude;
    float altitude;
    float speed;
    float bearing;
};

struct Station {
    int id;
};

class LoRaProtocolController : public QObject
{
    Q_OBJECT
public:
    explicit LoRaProtocolController(QObject *parent = nullptr);
    void initSerial(QString portName);
    Q_INVOKABLE void requestSend();
    Q_INVOKABLE void sendLora(QString id);

signals:
    void updateBus(BusItem *bus);
    void receivedRespond(int id);

public slots:
    void requestETA(QJsonObject obj);

    void runLora();
    void sendLora();
    void initTimer();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void on_socketReadyRead();

private:
    double calculateDistance(float lat1, float lon1, float lat2, float lon2);
    double toRadians(double degree);

    uint8_t calculateChecksum(const char *arr, int start, int end);

private:
    QThread mThread;

    QTimer *mLoRaRunTimer;
    QTimer *mLoRaResendTimer;

    QSerialPort mSerial;
    QString mPortName;
    QByteArray mBuffer;

    QByteArray mDataSend;
    bool mHaveSendRequest;
    int mSendCounter;

    Header mCurrentHeader;
    LoRaData mCurrentLoRaData;
    uint8_t mCurrentChecksum;

    qint64 mPreviousTimeStamp;

    int currSeq;

    int noErr;

    int mCurrRouteIDSend;

    QTcpSocket *mSocket;
    BusItem *tmpItem;

    const int mDataSize = sizeof(Header) + sizeof(LoRaData) + sizeof(uint8_t) + 2 * sizeof(char);
    const int mDataSendSize = sizeof(Station)  + 2 * sizeof(char);
};

#endif // LORAPROTOCOLCONTROLLER_H
