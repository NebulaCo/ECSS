#include "session.h"

Session::Session(int i, QString sT, int t) {
    intensityLevel = i;
    sessionType = sT;
    duration = t;
    timeLeft = t;

    timer = new QTimer(this);
}

Session::~Session() {
    delete timer;
}

int Session::getIntensityLvl() const{ return intensityLevel; }

QString Session::getSessionType() const{ return sessionType; }

int Session::getDuration() const{ return duration; }

QTimer *Session::getTimer() const { return timer; }

int Session::getTimeLeft() const { return timeLeft; }

void Session::setIntensity(int i){
    intensityLevel = i;
}

void Session::decrementTimeLeft(){
    timeLeft -= 1;
}


