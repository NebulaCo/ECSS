#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT(checkPress()));
    connect(ui->intensityUp, SIGNAL(pressed()), this, SLOT(checkPress()));
    connect(ui->intensityDown, SIGNAL(pressed()), this, SLOT(checkPress()));

    powerStatus = false;
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(togglePowerButton()));
    connect(ui->intensityUp, SIGNAL(released()), this, SLOT(toggleIntensityUp()));
    connect(ui->intensityDown, SIGNAL(released()), this, SLOT(toggleIntensityDown()));

    batteryLevel = 8;
    currentGroup = -1;
    currentSession = -1;

    pi_scene = new QGraphicsScene(this);
    ui->powerIndicator->setScene(pi_scene);

    initalizeVectors();
    initializeScreen();


//    QPixmap rtb (":/images/symbols/sessions/Red_TOP_R.png");
//    ui->rightTopBar->setPixmap(rtb.scaled(50, 50, Qt::KeepAspectRatio));

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

    groupVector.append(ui->group1);
    groupVector.append(ui->group2);
    groupVector.append(ui->group3);
    groupVector.append(ui->group4);

    sessionVector.append(ui->session1);
    sessionVector.append(ui->session2);
    sessionVector.append(ui->session3);
    sessionVector.append(ui->session4);
    sessionVector.append(ui->session5);
    sessionVector.append(ui->session6);
    sessionVector.append(ui->session7);
    sessionVector.append(ui->session8);

}

void MainWindow::initializeScreen(){
    QString str;
    int i;
    for (i = 0; i < barVector.size(); i++){
        str = QString::number(i+1);
        QPixmap numOff (":/images/symbols/bars/bar" + str + "off.png");
        barVector.at(i)->setPixmap(numOff.scaled(50, 100, Qt::KeepAspectRatio));
    }

    for (i = 0; i < groupVector.size(); i++){
        str = QString::number(i+1);
        QPixmap groupOff (":/images/symbols/groups/group" + str + "off.png");
        groupVector.at(i)->setPixmap(groupOff.scaled(75, 100, Qt::KeepAspectRatio));
    }

    for (i = 0; i < sessionVector.size(); i++){
        str = QString::number(i+1);
        QPixmap sessionOff (":/images/symbols/sessions/session" + str + "off.png");
        sessionVector.at(i)->setPixmap(sessionOff.scaled(75, 50, Qt::KeepAspectRatio));
    }
}

void MainWindow::displayBatteryLevel(){
    QString str;
    int i;
    for (i = 0; i < batteryLevel; i++){
        str = QString::number(i+1);
        QPixmap numOn (":/images/symbols/bars/bar"+str+"on.png");
        barVector.at(i)->setPixmap(numOn.scaled(50, 50, Qt::KeepAspectRatio));
    }
    for (i = batteryLevel; i < 8; i++){
        str = QString::number(i+1);
        QPixmap numOff (":/images/symbols/bars/bar"+str+"off.png");
        barVector.at(i)->setPixmap(numOff.scaled(50, 50, Qt::KeepAspectRatio));
    }
}



void MainWindow::checkPress() {
    buttonTimer.restart();
}

void MainWindow::updateScreen(){
    int i;
    QString str;
    if (currentGroup != -1){
        for (i = 0; i < groupVector.size(); i++){
            str = QString::number(i+1);
            if (i == currentGroup){
                QPixmap groupOn (":/images/symbols/groups/group" + str + "on.png");
                groupVector.at(i)->setPixmap(groupOn.scaled(75,100, Qt::KeepAspectRatio));
            } else {
                QPixmap groupOff (":/images/symbols/groups/group" + str + "off.png");
                groupVector.at(i)->setPixmap(groupOff.scaled(75, 100, Qt::KeepAspectRatio));
            }
        }
    }

    if (currentSession != -1){
        for (i = 0; i < sessionVector.size(); i++){
            str = QString::number(i+1);
            if (i == currentSession){
                QPixmap sessionOn (":/images/symbols/sessions/session" + str + "on.png");
                sessionVector.at(i)->setPixmap(sessionOn.scaled(75,100, Qt::KeepAspectRatio));
            } else {
                QPixmap sessionOff (":/images/symbols/sessions/session" + str + "off.png");
                sessionVector.at(i)->setPixmap(sessionOff.scaled(75, 100, Qt::KeepAspectRatio));
            }
        }
    }

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
    } else if (powerStatus){
        //Cycling
        currentGroup = (currentGroup == 3) ? 0 : ++currentGroup;
        updateScreen();
    }
}


void MainWindow::toggleIntensityUp(){
    if (powerStatus){
        currentSession = (currentSession == 7) ? 0 : ++currentSession;
        updateScreen();
    }
}

void MainWindow::toggleIntensityDown(){
    if (powerStatus){
        currentSession = (currentSession == 0) ? 7 : --currentSession;
        updateScreen();
    }
}
