#include "session.h"

Session::Session(int i, QString sT, int t) {
    intensityLevel = i;
    sessionType = sT;
    duration = t;

    timer = new QTimer();
}

Session::~Session() {
    delete timer;
}

int Session::getIntensityLvl() const{
    return intensityLevel;
}

QString Session::getSessionType() const{
    return sessionType;
}

int Session::getDuration() const{
    return duration;
}

void Session::setIntensity(int i){
    intensityLevel = i;
}

QTimer *Session::getTimer() const
{
    return timer;
}
