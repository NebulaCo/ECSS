#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDateTime>

class Session {

    public:
        Session(int i, QString sT, int t);
        int getIntensityLvl();
        QString getSessionType();
        int getDuration();
        void setIntensity(int i);
    private:
        int intensityLevel;
        QString sessionType;
        int duration;

};

#endif // SESSION_H
