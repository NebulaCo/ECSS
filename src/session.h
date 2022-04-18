#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>

/* Purpose of class: Session object to hold information about a session

   Data Members:
   - int intensityLevel: An integer representation of intensity level of the session
   - QString sessionType: a QString representation of the session type
   - QTimer* timer: A QTimer object to keep track of how long a session should last
   - int duration: An integer representation of duration of the session
   - int timeLeft: An integer representation of time left of the session
   - bool isShortCESMode: bool representation to trck if the session is short-pulse or 50% heavy duty


   Class functions:
   -getters and setters for data members

   void decrementTimeLeft(): decrease time left by 1
 */

class Session: public QObject{

    Q_OBJECT

    public:
        Session(int i, int sT, int t);
        ~Session();

        int getIntensityLvl() const;
        QString getSessionType() const;
        int getDuration() const;
        int getTimeLeft() const;
        bool getIsShortCESMode() const;
        QTimer* getTimer() const;
        void decrementTimeLeft();
        void setTimeLeft(int);
        void setIntensity(int i);

        QString toString();

private:
        int intensityLevel;
        QString sessionType;
        QTimer* timer;
        int duration;
        int timeLeft;
        bool isShortCESMode;

        void setSessionType(int);
};

#endif // SESSION_H
