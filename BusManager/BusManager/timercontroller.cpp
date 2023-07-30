#include "timercontroller.h"

TimerController::TimerController(QObject *parent)
    : QObject{parent}
{
    connect(&mResendTimer, SIGNAL(timeout()), this, SLOT(notifyResendTimeout()));
}

void TimerController::startResendTimer()
{
    mResendTimer.start(DURATION_RESEND_LORA_DATA);
}

void TimerController::stopResendTimer()
{
    mResendTimer.stop();
}

void TimerController::notifyResendTimeout()
{
    emit timeoutResendTimer();
    mResendTimer.stop();
}
