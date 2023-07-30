#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "config.h"

class TimerController : public QObject
{
    Q_OBJECT
public:
    explicit TimerController(QObject *parent = nullptr);

signals:
    void timeoutResendTimer();

public slots:
    void startResendTimer();
    void stopResendTimer();

private slots:
    void notifyResendTimeout();

private:
    QTimer mResendTimer;

};

#endif // TIMERCONTROLLER_H
