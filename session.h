#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>

class Session: public QObject{

    Q_OBJECT

    public:
        Session(int i, int sT, int t);
        ~Session();
        int getIntensityLvl() const;
        QString getSessionType() const;
        int getDuration() const;
        int getTimeLeft() const;
        void setIntensity(int i);
        QTimer* getTimer() const;
        void decrementTimeLeft();
        void setTimeLeft(int);

        QString toString();

private:
        int intensityLevel;
        QString sessionType;
        QTimer* timer;
        int duration;
        int timeLeft;
        void setSessionType(int);


};

#endif // SESSION_H
