#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qelapsedtimer.h"
#include <QGraphicsView>
#include <QVector>
#include <QLabel>
#include <QTime>
#include <QListWidget>
#include <QDebug>
#include <QtMath>

#include "session.h"

/* Class purpose: To act as main control of the device application

    Data members:

    QVector <QLabel*> barVector:
    QVector <QLabel*> groupVector:
    QVector <QLabel*> sessionVector:

    //Vector of sessions
    QVector <Session*> sessionHistory:
    QStringList sessionHistoryView:

    //Power indicator scene
    QGraphicsScene *pi_scene:
    //Record indicator scene
    QGraphicsScene *rec_scene:

    QElapsedTimer buttonTimer:
    QTimer* blinkTimer:                 keep track of blink timer
    QTimer* lowBatteryTimer:            keep track of how much time left for low battery blinking

    QListWidget *activeQListWidget:


    bool powerStatus:                   wheter power is on or not
    bool recordSession:                 whether to record the session or not
    int currentGroup:                   current group
    int currentSessionType:             current session type
    int currentIntensity:               current intensity
    float battery:                      battery of the device
    double userSessionTime:             user's session time
    int connection:                     current connection. 1 = bad connection; 2 = okay connection; 3 = excellent connection
    Session* currentSession:            current session
    bool sessionRunning:                whether session is running or not
    bool sessionPaused = false:         whether session is paused or not
    int blinkTimeLeft = 8:              keep track of how much time left for blink


    Functions:

    void initalizeVectors():            .
    void updateTreatmentHistory():      .
    void updateScreen():                .
    void displayEmptyBar():             switch off all the 8 bars off the bas
    void displayBarLevel(int n):        switch on n number of bars on graph starting from the bottom
    void displayBarSingleLight(int n):  switch on n_th bar from the bottom
    void turnOff():                     Turn off the machine
    void softOff():                     Perform a soft-off
    void delay(float n):                Sleep for n seconds
    void initSessionTimer(QTimer*):     Initialize the session timer
    void drainBattery():                Drain the battery as a function of length of therapy, intensity, and conneciton to skin per second. Then update the screen.
    void updateBattery(float):          Update the battery to new value
    void blinkCESMode():                Blink CES mode light
    void blinkLowBattery(float):        Blink if battery is low
    void blinkBadConnection():          Blink if connection is bad
    bool canStartSession():             Return boolean indicating if session can start or not
    bool connectionTest():              Perform connection test
    void badConnection():               Display bad connection on graph
    void okayConnection():              Display okay conneciton on graph
    void excellentConnection():         Display good connection on graph
    void blinkSelectedSession(int):     Blink selected session
    void pauseSession():                Pause currently running session
    void resumeSession():               Pause paused session

    void displayBattery():              Display battery on bar graph
    void updateSessionTimer():          Update session timer and check if session has ended or not
    void checkPress():
    void togglePowerButton():
    void toggleIntensityUp():
    void toggleIntensityDown():
    void toggleDurationUp():
    void toggleDurationDown():
    void startSession():                Start a session
    void changeConnection():            Update the connection. Resume/pause session if connection is changed and session is running.
    void earConnect():                  Update ear connection
    void toggleRecording():
    void updatelowBatteryTimer():       Update timer for blinking low battery
    void updateCriticalLowBatteryTimer():   Update timer for blinking critically low battery timer and turn off the machine


*/

#define BAR_COUNT 8
#define GROUP_COUNT 3
#define SESSION_TYPE_COUNT 8
#define MAX_INTENSITY 8
#define MAX_SESSION_LENGTH 180
#define MIN_SESSION_LENGTH 5


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QVector <QLabel*> barVector;
    QVector <QLabel*> groupVector;
    QVector <QLabel*> sessionVector;

    //Vector of sessions
    QVector <Session*> sessionHistory;
    QStringList sessionHistoryView;

    //Power indicator scene
    QGraphicsScene *pi_scene;
    //Record indicator scene
    QGraphicsScene *rec_scene;

    QElapsedTimer buttonTimer;
    QTimer* blinkTimer;
    QTimer* lowBatteryTimer;

    QListWidget *activeQListWidget;


    bool powerStatus;
    bool recordSession;
    int currentGroup;
    int currentSessionType;
    int currentIntensity;
    float battery;
    double userSessionTime;
    // 1 = bad connection; 2 = okay connection; 3 = excellent connection
    int connection;
    Session* currentSession;
    bool sessionRunning;
    bool sessionPaused = false;
    int blinkTimeLeft = 8;


    void initalizeVectors();
    void updateTreatmentHistory();
    void updateScreen();
    void displayEmptyBar();
    void displayBarLevel(int);
    void displayBarSingleLight(int);
    void turnOff();
    void softOff();
    void delay(float);
    void initSessionTimer(QTimer*);
    void drainBattery();
    void updateBattery(float);
    void blinkCESMode();
    void blinkLowBattery(float);
    void blinkBadConnection();
    bool canStartSession();
    bool connectionTest();
    void badConnection();
    void okayConnection();
    void excellentConnection();
    void blinkSelectedSession(int);
    void pauseSession();
    void resumeSession();

private slots:
    void displayBattery();
    void updateSessionTimer();
    void checkPress();
    void togglePowerButton();
    void toggleIntensityUp();
    void toggleIntensityDown();
    void toggleDurationUp();
    void toggleDurationDown();
    void startSession();
    void changeConnection();
    void earConnect();
    void toggleRecording();

    void updatelowBatteryTimer();
    void updateCriticalLowBatteryTimer();
};
#endif // MAINWINDOW_H
