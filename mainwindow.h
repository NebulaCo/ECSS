#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qelapsedtimer.h"
#include <QGraphicsView>

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

    //Power indicator scene
    QGraphicsScene *pi_scene;
    QGraphicsScene *n1_scene;

private slots:
    void checkPress();
    void togglePowerButton();
    void toggleIntensityButton();
};
#endif // MAINWINDOW_H
