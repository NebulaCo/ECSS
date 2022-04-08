#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qelapsedtimer.h"
#include <QGraphicsView>
#include <QVector>
#include <QLabel>

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
    int currentSession;

    //Power indicator scene
    QGraphicsScene *pi_scene;
    QGraphicsScene *n1_scene;

    int batteryLevel;
    void displayBatteryLevel();
    void updateScreen();


    void initalizeVectors();
    void initializeScreen();

private slots:
    void checkPress();
    void togglePowerButton();
    void toggleIntensityUp();
    void toggleIntensityDown();
};
#endif // MAINWINDOW_H
