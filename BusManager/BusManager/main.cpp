#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QtWebEngine/qtwebengineglobal.h>
#include <QObject>
#include <QQmlContext>
#include "loraprotocolcontroller.h"
#include "busstationcontroller.h"
//#include "timercontroller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    BusStationController bsc;

    LoRaProtocolController lora;
    QObject::connect(&lora, SIGNAL(updateBus(BusItem*)), &bsc, SLOT(updateBus(BusItem*)));
    QObject::connect(&lora, SIGNAL(receivedRespond(int)), &bsc, SLOT(handleResponse(int)));

//    TimerController timer;
//    QObject::connect(&lora, SIGNAL(startResendTimer()), &timer, SLOT(startResendTimer()));
//    QObject::connect(&lora, SIGNAL(stopResendTimer()), &timer, SLOT(stopResendTimer()));
//    QObject::connect(&timer, SIGNAL(timeoutResendTimer()), &timer, SLOT(notifyResendTimeout()));

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("BusModel", &bsc);
    engine.rootContext()->setContextProperty("Lora", &lora);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
