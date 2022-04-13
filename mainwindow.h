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

    void updatelowBatteryTimer();
    void updateCriticalLowBatteryTimer();
    void updateBlinkCESModeTimer();
};
#endif // MAINWINDOW_H
