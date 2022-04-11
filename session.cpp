#include "session.h"

Session::Session(int i, int sesh, int t) {
    intensityLevel = i;
    setSessionType(sesh);
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

void Session::setSessionType(int sesh){
    switch(sesh){
        case 0:
            sessionType = "MET";
            break;
        case 1:
            sessionType = "Sub-Delta";
            break;
        case 2:
            sessionType = "Delta";
            break;
        case 3:
            sessionType = "Theta";
            break;
        case 4:
            sessionType = "Alpha";
            break;
        case 5:
            sessionType = "SMR";
            break;
        case 6:
            sessionType = "Beta";
            break;
        case 7:
            sessionType = "100 Hz";
            break;
        default:
            sessionType = "Invalid Session Type";
    }

}



