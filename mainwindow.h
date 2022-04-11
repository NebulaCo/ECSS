#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qelapsedtimer.h"
#include <QGraphicsView>
#include <QVector>
#include <QLabel>
#include <QTime>

#include "session.h"

#define BAR_COUNT 8
#define GROUP_COUNT 3
#define SESSION_TYPE_COUNT 8
#define MAX_INTENSITY 8


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

    QVector <QLabel*> barVector;
    QVector <QLabel*> groupVector;
    QVector <QLabel*> sessionVector;

    int currentGroup;
    int currentGroupDuration;
    int currentSessionType;

    int currentIntensity;

    // Connection 1 = bad connection
    //            2 = okay connection
    //            3 = excellent connection
    int connection;

    //Power indicator scene
    QGraphicsScene *pi_scene;
    QGraphicsScene *n1_scene;

    float battery;

    Session* currentSession;
    bool sessionRunning;

    void displayBatteryLevel(float);
    void updateScreen();


    void initalizeVectors();
    void initializeScreen();

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
    void barSingleLight(int);


private slots:
    void updateTimer();
    void checkPress();
    void togglePowerButton();
    void toggleIntensityUp();
    void toggleIntensityDown();
    void startSession();
    void changeConnection();
    void earConnect(int);
};
#endif // MAINWINDOW_H
