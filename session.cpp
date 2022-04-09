#include "session.h"

Session::Session(int i, QString sT, int t) {
    intensityLevel = i;
    sessionType = sT;
    duration = t;
}

int Session::getIntensityLvl(){
    return intensityLevel;
}

QString Session::getSessionType(){
    return sessionType;
}

int Session::getDuration(){
    return duration;
}

void Session::setIntensity(int i){
    intensityLevel = i;
}
