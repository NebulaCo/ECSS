#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT(checkPress()));
//    connect(ui->intensityUp, SIGNAL(pressed()), this, SLOT(checkPress()));
//    connect(ui->intensityDown, SIGNAL(pressed()), this, SLOT(checkPress()));
    powerStatus = false;
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(togglePowerButton()));


    pi_scene = new QGraphicsScene(this);
    ui->powerIndicator->setScene(pi_scene);

    QPixmap oneOff ("/home/student/Desktop/comp3004finalproject/images/bar1off.png");
    ui->bar1->setPixmap(oneOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap twoOff ("/home/student/Desktop/comp3004finalproject/images/bar2off.png");
    ui->bar2->setPixmap(twoOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap threeOff ("/home/student/Desktop/comp3004finalproject/images/bar3off.png");
    ui->bar3->setPixmap(threeOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap fourOff ("/home/student/Desktop/comp3004finalproject/images/bar4off.png");
    ui->bar4->setPixmap(fourOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap fiveOff ("/home/student/Desktop/comp3004finalproject/images/bar5off.png");
    ui->bar5->setPixmap(fiveOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap sixOff ("/home/student/Desktop/comp3004finalproject/images/bar6off.png");
    ui->bar6->setPixmap(sixOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap sevenOff ("/home/student/Desktop/comp3004finalproject/images/bar7off.png");
    ui->bar7->setPixmap(sevenOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap eightOff ("/home/student/Desktop/comp3004finalproject/images/bar8off.png");
    ui->bar8->setPixmap(eightOff.scaled(50, 50, Qt::KeepAspectRatio));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::checkPress() {
    buttonTimer.restart();
}

void MainWindow::togglePowerButton(){
    if (buttonTimer.elapsed() >= 2000){
        powerStatus = powerStatus ? false: true;

        if (powerStatus) {
            qInfo() << "Machine turned on.";
            pi_scene->setBackgroundBrush(Qt::green);

        } else {
            qInfo() << "Machine turned off.";
            pi_scene->setBackgroundBrush(Qt::white);
        }
    } else {
        //Cycling
        qInfo() << "Doing some other function.";
        //Move this to turning on block in if-else

    }
}



void MainWindow::toggleIntensityButton(){
    QString s1 = QString::number(8);

    QPixmap connectionBar ();

}
