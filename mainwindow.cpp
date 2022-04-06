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

    batteryLevel = 8;

    pi_scene = new QGraphicsScene(this);
    ui->powerIndicator->setScene(pi_scene);

    initalizeVectors();
    initializeScreen();


    QPixmap rtb (":/images/symbols/sessions/Red_TOP_R.png");
    ui->rightTopBar->setPixmap(rtb.scaled(50, 50, Qt::KeepAspectRatio));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initalizeVectors(){
    barVector.append(ui->bar1);
    barVector.append(ui->bar2);
    barVector.append(ui->bar3);
    barVector.append(ui->bar4);
    barVector.append(ui->bar5);
    barVector.append(ui->bar6);
    barVector.append(ui->bar7);
    barVector.append(ui->bar8);
}

void MainWindow::initializeScreen(){
    QString str;
    for (int i = 0; i < 8; i++){
        str = QString::number(i+1);
        QPixmap numOff (":/images/symbols/bars/bar" + str + "off.png");
        barVector.at(i)->setPixmap(numOff.scaled(50, 50, Qt::KeepAspectRatio));
    }

}

void MainWindow::displayBatteryLevel(){
    QString str;
    for (int i = 0; i < batteryLevel; i++){
        str = QString::number(i+1);
        QPixmap numOn (":/images/symbols/bars/bar"+str+"on.png");
        barVector.at(i)->setPixmap(numOn.scaled(50, 50, Qt::KeepAspectRatio));
    }
    for (int i = batteryLevel; i < 8; i++){
        str = QString::number(i+1);
        QPixmap numOff (":/images/symbols/bars/bar"+str+"off.png");
        barVector.at(i)->setPixmap(numOff.scaled(50, 50, Qt::KeepAspectRatio));
    }
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
            displayBatteryLevel();


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



}
