#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>

class Session: public QObject{

    Q_OBJECT

    public:
        Session(int i, QString sT, int t);
        ~Session();
        int getIntensityLvl() const;
        QString getSessionType() const;
        int getDuration() const;
        int getTimeLeft() const;
        void setIntensity(int i);
        QTimer* getTimer() const;
        void decrementTimeLeft();

private:
        int intensityLevel;
        QString sessionType;
        QTimer* timer;
        int duration;
        int timeLeft;


};

#endif // SESSION_H
