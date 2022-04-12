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

#include "session.h"

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

    QElapsedTimer buttonTimer;
    bool powerStatus;

    bool recordSession;

    QVector <QLabel*> barVector;
    QVector <QLabel*> groupVector;
    QVector <QLabel*> sessionVector;

    //todo: Vector of sessions
    QVector <Session*> sessionHistory;
    QStringList sessionHistoryView;


    int currentGroup;
    int currentSessionType;

    int currentIntensity;

    // Connection 1 = bad connection
    //            2 = okay connection
    //            3 = excellent connection
    int connection;

    //Power indicator scene
    QGraphicsScene *pi_scene;
    //Record indicator scene
    QGraphicsScene *rec_scene;
    QTimer* temp;


    QListWidget *activeQListWidget;




    float battery;
    double userSessionTime;

    Session* currentSession;
    bool sessionRunning;
    bool sessionPaused = false;

    int blinkTimeLeft = 6;

    void displayBarLevel(int);
    void displayBattery(float);
    void updateScreen();


    void initalizeVectors();

    bool connectionTest();
    void badConnection();
    void okayConnection();
    void excellentConnection();
    void turnOff();
    bool canStartSession();
    void flashSelectedSession(int);
    void initTimer(QTimer*);

    void drainBattery();
    void changeBattery(float);

    void softOff();
    void delay(float);
    void displayBarSingleLight(int);

    void blinkBadConnection();
    void resumeSession();
    void pauseSession();

    void updateTreatmentHistory();


private slots:
    void updateTimer();
    void updateBlinkTimer();
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

};
#endif // MAINWINDOW_H
