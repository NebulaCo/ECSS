#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDateTime>

class Session{

    public:
        Session(int i, QString sT, int t);
        ~Session();
        int getIntensityLvl() const;
        QString getSessionType() const;
        int getDuration() const;
        void setIntensity(int i);
        QTimer* getTimer() const;

    private:
        int intensityLevel;
        QString sessionType;
        int duration;
        QTimer* timer;

};

#endif // SESSION_H
