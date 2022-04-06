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

    batterLevel = 8;

    pi_scene = new QGraphicsScene(this);
    ui->powerIndicator->setScene(pi_scene);

    QPixmap oneOff (":/images/bars/resources/bar1off.png");
    ui->bar1->setPixmap(oneOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap twoOff (":/images/bars/bar2off.png");
    ui->bar2->setPixmap(twoOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap threeOff (":/images/bars/bar3off.png");
    ui->bar3->setPixmap(threeOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap fourOff (":/images/bars/bar4off.png");
    ui->bar4->setPixmap(fourOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap fiveOff (":/images/bars/bar5off.png");
    ui->bar5->setPixmap(fiveOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap sixOff (":/images/bars/bar6off.png");
    ui->bar6->setPixmap(sixOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap sevenOff (":/images/bars/bar7off.png");
    ui->bar7->setPixmap(sevenOff.scaled(50, 50, Qt::KeepAspectRatio));
    QPixmap eightOff (":/images/bars/bar8off.png");
    ui->bar8->setPixmap(eightOff.scaled(50, 50, Qt::KeepAspectRatio));

//    barVector.append(ui->bar1);
//    QPixmap pOn (":/images/bars/bar1on.png");
//    barVector.at(0)->setPixmap(pOn.scaled(50, 50, Qt::KeepAspectRatio));



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

void MainWindow::displayBatteryLevel(){



    for (int i = 0; i < batterLevel; i++){

        QString s1 = QString::number(i);
        QPixmap pOn (":/images/bars/bar"+s1+"on.png");
        ui->bar1->setPixmap(pOn.scaled(50, 50, Qt::KeepAspectRatio));

    }
}



void MainWindow::toggleIntensityButton(){
    QString s1 = QString::number(8);

    QPixmap connectionBar ();

}
