#include "loraprotocolcontroller.h"

LoRaProtocolController::LoRaProtocolController(QObject *parent)
    : QObject{parent}
{
    initSerial("COM3");
    currSeq = -1;

    connect(&mThread, SIGNAL(started()), this, SLOT(initTimer()));

    mLoRaRunTimer = new QTimer();
    mLoRaRunTimer->setInterval(10);
    connect(mLoRaRunTimer, SIGNAL(timeout()), this, SLOT(runLora()));
    mLoRaRunTimer->start();

    mLoRaResendTimer = new QTimer();
    connect(mLoRaResendTimer, SIGNAL(timeout()), this, SLOT(sendLora()));

    //this->moveToThread(&mThread);

    mHaveSendRequest = 0;
    mSendCounter = 0;

    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::connected, this, &LoRaProtocolController::onSocketConnected);
    connect(mSocket, &QTcpSocket::disconnected, this, &LoRaProtocolController::onSocketDisconnected);
    connect(mSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(mSocket, &QTcpSocket::readyRead, this, &LoRaProtocolController::on_socketReadyRead);

    //mThread.start();
}

void LoRaProtocolController::initSerial(QString portName)
{
    mPortName = portName;

    mSerial.setPortName(mPortName);
    if(!mSerial.setBaudRate(QSerialPort::Baud19200))
        qDebug() << mSerial.errorString();
    //        if(!mSerial.setDataBits(QSerialPort::Data8))
    //            qDebug() << mSerial.errorString();
    //        if(!mSerial.setParity(QSerialPort::EvenParity))
    //            qDebug() << mSerial.errorString();
    //        if(!mSerial.setFlowControl(QSerialPort::HardwareControl))
    //            qDebug() << mSerial.errorString();
    //        if(!mSerial.setStopBits(QSerialPort::OneStop))
    //            qDebug() << mSerial.errorString();
    if(!mSerial.open(QIODevice::ReadWrite))
        qDebug() << mSerial.errorString();
    else qDebug() << "Connect to LoRa module successfully";
}

void LoRaProtocolController::requestSend()
{
    mHaveSendRequest = 1;
}

void LoRaProtocolController::sendLora(QString id)
{
    qDebug() << "-----------------------------------------Start SendLora111";
    char tmpData3[20];
    char startChar = '*', endChar = '#';
    mSendCounter = 0;
    mCurrRouteIDSend = id.toInt();
    mLoRaResendTimer->stop();
    qDebug() << "======= " << id.toInt();
    Station tmpStation = { id.toInt()};

    int offset = 0;
    memcpy(&tmpData3[offset], &startChar, sizeof(char));
    offset += sizeof(char);
    memcpy(&tmpData3[offset], &tmpStation, sizeof(tmpStation));
    offset += sizeof(tmpStation);
    memcpy(&tmpData3[offset], &endChar, sizeof(char));

    mSerial.write(QByteArray::fromRawData(tmpData3, mDataSendSize));
    if(!mSerial.waitForBytesWritten()){
        qDebug() << "ERRORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR111";
    }
    qDebug() << "SENTTTTTTTTTTTTTTTTTTTTTTTT111";
    mLoRaResendTimer->start(DURATION_RESEND_LORA_DATA);
}

void LoRaProtocolController::requestETA(QJsonObject obj)
{
    QString serverIP = "127.0.0.1";
    quint16 serverPort = 12345;

    QJsonDocument jsonDocument(obj);
    QByteArray jsonData = jsonDocument.toJson();

    mSocket->connectToHost(serverIP, serverPort);

    if (mSocket->waitForConnected(5000))
    {
        mSocket->write(jsonData);
        mSocket->waitForBytesWritten(1000);
    }
}

void LoRaProtocolController::runLora()
{
    if(true){
        mBuffer.append(mSerial.readAll());
        while (mSerial.waitForReadyRead(10))
            mBuffer += mSerial.readAll();

        if(mBuffer.size() > 0){

            qDebug() << "== buffer: " << QString::fromStdString(mBuffer.toStdString());
            int i = 0;
            while(i < mBuffer.size() && mBuffer[i] != '*') i++;

            qDebug() << "--- " << mBuffer.size() << " -  i =" << i;
            if(i > mBuffer.size()) {
                mBuffer.clear();
                return;//continue;
            }

            int i1 = i + 1;
            while(i1 < mBuffer.size() && mBuffer[i1] != '*') i1++;
            if(i1 < mBuffer.size() && i1 < i + mDataSize){
                mBuffer.remove(0, i1);
                return;//continue;
            }

            if(i + mDataSize - 1 < mBuffer.size() && mBuffer[i + mDataSize - 1] == '#'){
                int j = i + sizeof(char);
                const char* tmpdata = mBuffer.constData();
                memcpy(&mCurrentHeader, &tmpdata[j], sizeof(Header));
                j += (sizeof(Header));
                memcpy(&mCurrentLoRaData, &tmpdata[j], sizeof(LoRaData));
                j += (sizeof(LoRaData));
                memcpy(&mCurrentChecksum, &tmpdata[j], sizeof(uint8_t));
                j += (sizeof(uint8_t));

                uint8_t tmpChecksum = calculateChecksum(tmpdata, i + sizeof(char), i + sizeof(Header) + sizeof(LoRaData));
                qDebug() << "========= checksum: " << mCurrentChecksum << tmpChecksum;

                if(mCurrentChecksum != tmpChecksum){
                    qDebug() << "--- Checksum not matchhhhhhhhh";
                    mBuffer.remove(0, i + mDataSize);
                    return;
                }

                if(mCurrentHeader.seq == mCurrRouteIDSend){
                    qDebug() << "################# Reply from esp";
                    mLoRaResendTimer->stop();
                    emit receivedRespond(mCurrRouteIDSend);
                }
                qDebug() << "--- noErr: " << noErr << ", currSeq: " << currSeq << ", busSeq: " << mCurrentHeader.seq;

                float tmpd = calculateDistance(BUS_STATION_LATITUDE, BUS_STATION_LONGITUDE, mCurrentLoRaData.latitude, mCurrentLoRaData.longitude);

                qDebug() << "Bus seq:" << mCurrentHeader.seq << "\n" <<
                            "Bus ID:" << QString::number(mCurrentHeader.bus_id) << "\n" <<
                            "Temp:" << mCurrentLoRaData.temperature << "\n" <<
                            "Humi:" << mCurrentLoRaData.huminity << "\n" <<
                            "Long:" << mCurrentLoRaData.longitude << "\n" <<
                            "Lat:" << mCurrentLoRaData.latitude << "\n" <<
                            "Alt:" << mCurrentLoRaData.altitude << "\n" <<
                            "Speed:" << mCurrentLoRaData.speed << "\n" <<
                            "Distance:" << tmpd << " - " << QString::number(tmpd) << "\n" <<
                            "Peoples:" << mCurrentLoRaData.peoples << "\n";

                tmpItem = new BusItem();
                if(mCurrentHeader.bus_id == 1){
                    tmpItem->setBusId("59A 12345");
                    tmpItem->setBusRoute("53");
                    tmpItem->setMainStations("Bến Xe Buýt Sài Gòn - Khu Chế Xuất Linh Trung - Đại Học Quốc Gia");
                }
                else{
                    tmpItem->setBusId("N/A");
                }
                tmpItem->setTemperature(mCurrentLoRaData.temperature);
                tmpItem->setHuminity(mCurrentLoRaData.huminity);
                tmpItem->setLongitude(mCurrentLoRaData.longitude);
                tmpItem->setLatitude(mCurrentLoRaData.latitude);
                tmpItem->setAltitude(mCurrentLoRaData.altitude);
                tmpItem->setSpeed(mCurrentLoRaData.speed);
                tmpItem->setPeoples(mCurrentLoRaData.peoples);
                tmpItem->setTimeStamp(QDateTime::currentMSecsSinceEpoch());
                tmpItem->setTimeArrival(0);
                tmpItem->setDistance(QString::number(tmpd));

                QJsonObject jsonObject;
                jsonObject["lon"] = mCurrentLoRaData.longitude;
                jsonObject["lat"] = mCurrentLoRaData.latitude;
                jsonObject["bearing"] = mCurrentLoRaData.bearing;
                jsonObject["speed"] = mCurrentLoRaData.speed;
                requestETA(jsonObject);

                mBuffer.remove(0, i + mDataSize);
            }
            else{
                mBuffer.remove(0, i + 1);
            }
        }


        if(mHaveSendRequest){
            qDebug() << "9999999999999999999999999999999999";
            mHaveSendRequest = 0;
            mSendCounter = 0;
            sendLora();
        }
    }
}

void LoRaProtocolController::sendLora()
{
    if(mSendCounter++ <= TIMES_RESEND_LORA_DATA){
        qDebug() << "----------------------------------------- SendLora = " << mSendCounter;
        char tmpData3[20];
        char startChar = '*', endChar = '#';
        mCurrRouteIDSend = 53;
        Station tmpStation = {mCurrRouteIDSend};

        int offset = 0;
        memcpy(&tmpData3[offset], &startChar, sizeof(char));
        offset += sizeof(char);
        memcpy(&tmpData3[offset], &tmpStation, sizeof(tmpStation));
        offset += sizeof(tmpStation);
        memcpy(&tmpData3[offset], &endChar, sizeof(char));

        mSerial.write(QByteArray::fromRawData(tmpData3, mDataSendSize));
        if(!mSerial.waitForBytesWritten()){
            qDebug() << "ERRORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR";
        }
        qDebug() << "SENTTTTTTTTTTTTTTTTTTTTTTTT";
        mLoRaResendTimer->start(DURATION_RESEND_LORA_DATA);
    }
    else{
        qDebug() << "OVER 3 TIMES 1=1=1=1=1=1=1=1=1=1=";
        mLoRaResendTimer->stop();
    }
}

void LoRaProtocolController::initTimer()
{
    mLoRaResendTimer = new QTimer();
    connect(mLoRaResendTimer, SIGNAL(timeout()), this, SLOT(sendLora()));
    mLoRaResendTimer->moveToThread(&mThread);
}

void LoRaProtocolController::onSocketConnected()
{
    qDebug() << "Connected to server.";
}

void LoRaProtocolController::onSocketDisconnected()
{
    qDebug() << "Disconnected from server.";
}

void LoRaProtocolController::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
}

void LoRaProtocolController::on_socketReadyRead()
{
    QByteArray responseData = mSocket->readAll();
    QJsonDocument responseJson = QJsonDocument::fromJson(responseData);

    if (!responseJson.isNull()) {
        QJsonObject responseObj = responseJson.object();
        qDebug() << "Received response:" << responseObj;
        tmpItem->setTimeArrival(responseObj["time"].toDouble()/60);
        emit updateBus(tmpItem);
    }

    mSocket->disconnectFromHost();
}

double LoRaProtocolController::calculateDistance(float lat1, float lon1, float lat2, float lon2)
{
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dlong = lon2 - lon1;
    double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
            cos(lat1) * cos(lat2) *
            pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    double d = ans * R;

    qDebug() << "===== " << d;

    return d;
}

double LoRaProtocolController::toRadians(double degree)
{
    return (degree * ((M_PI) / 180));
}

uint8_t LoRaProtocolController::calculateChecksum(const char *arr, int start, int end)
{
    uint8_t checksum = 0;
    for (int i = start; i <= end; ++i) {
        checksum ^= arr[i];
    }
    return checksum;
}

