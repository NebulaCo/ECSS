#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

//    QPixmap checkButtonImage (":/images/symbols/buttons/check");
//    ui->checkButtonImage->setPixmap(checkButtonImage);

    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT(checkPress()));
    connect(ui->intensityUpButton, SIGNAL(pressed()), this, SLOT(checkPress()));
    connect(ui->intensityDownButton, SIGNAL(pressed()), this, SLOT(checkPress()));
    connect(ui->durationUpButton, SIGNAL(pressed()), this, SLOT(toggleDurationUp()));
    connect(ui->durationDownButton, SIGNAL(pressed()), this, SLOT(toggleDurationDown()));

    connect(ui->recordButton, SIGNAL(pressed()), this, SLOT(toggleRecording()));


    connect(ui->powerButton, SIGNAL(released()), this, SLOT(togglePowerButton()));
    connect(ui->intensityUpButton, SIGNAL(released()), this, SLOT(toggleIntensityUp()));
    connect(ui->intensityDownButton, SIGNAL(released()), this, SLOT(toggleIntensityDown()));

    connect(ui->checkButton, SIGNAL(released()), this, SLOT(startSession()));

    powerStatus = false;
    recordSession = false;
    userSessionTime = 60;
    //Admin


    battery = 100.0;
    //battery level spinbox
    connect(ui->batterySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeBattery);

    //connection spin box
    connect(ui->connectionComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::changeConnection);

    connect(ui->leftEarComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::earConnect);
    connect(ui->rightEarComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::earConnect);

    currentGroup = -1;
    currentSessionType = -1;

    currentIntensity = 0;
    connection = -1;
    sessionRunning = false;

    pi_scene = new QGraphicsScene(this);
    ui->powerIndicator->setScene(pi_scene);

    rec_scene = new QGraphicsScene(this);
    ui->recordIndicator->setScene(rec_scene);

    initalizeVectors();
    updateScreen();


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

    sessionVector.append(ui->session1);
    sessionVector.append(ui->session2);
    sessionVector.append(ui->session3);
    sessionVector.append(ui->session4);
    sessionVector.append(ui->session5);
    sessionVector.append(ui->session6);
    sessionVector.append(ui->session7);
    sessionVector.append(ui->session8);

}

void MainWindow::displayBarLevel(int bars){

//    int bars = int(battery / 12.5);
    QString str;
    int i;
    for (i = 0; i < bars; i++){
        str = QString::number(i+1);
        QPixmap numOn (":/images/symbols/bars/bar"+str+"on.png");
        barVector.at(i)->setPixmap(numOn.scaled(50, 50, Qt::KeepAspectRatio));
    }
    for (i = bars; i < BAR_COUNT; i++){
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

    if (!powerStatus){
        for (i = 0; i < sessionVector.size(); i++){
            str = QString::number(i+1);
            QPixmap sessionOff (":/images/symbols/sessions/session" + str + "off.png");
            sessionVector.at(i)->setPixmap(sessionOff.scaled(75, 100, Qt::KeepAspectRatio));
        }
        for (i = 0; i < groupVector.size(); i++){
            str = QString::number(i+1);
            QPixmap groupOff (":/images/symbols/groups/group" + str + "off.png");
            groupVector.at(i)->setPixmap(groupOff.scaled(75, 100, Qt::KeepAspectRatio));
        }
        ui->group3Screen->clear();

        for (i = 0; i < barVector.size(); i++){
            str = QString::number(i+1);
            QPixmap numOff (":/images/symbols/bars/bar" + str + "off.png");
            barVector.at(i)->setPixmap(numOff.scaled(50, 100, Qt::KeepAspectRatio));
        }

        QPixmap left_CES (":/images/symbols/staticgraphics/left_CES_off.png");
        QPixmap right_CES (":/images/symbols/staticgraphics/right_CES_off.png");
        QPixmap short_CES (":/images/symbols/staticgraphics/short_CES_off.png");
        QPixmap duty_CES (":/images/symbols/staticgraphics/duty_cycle_CES_off.png");
        ui->left_CES_label->setPixmap(left_CES.scaled(75, 100, Qt::KeepAspectRatio));
        ui->right_CES_label->setPixmap(right_CES.scaled(75, 100, Qt::KeepAspectRatio));
        ui->short_CES_label->setPixmap(short_CES.scaled(75, 100, Qt::KeepAspectRatio));
        ui->duty_CES_label->setPixmap(duty_CES.scaled(75, 100, Qt::KeepAspectRatio));

        rec_scene->setBackgroundBrush(Qt::white);

        return;
    }
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
    } else {
        for (i = 0; i < groupVector.size(); i++){
            str = QString::number(i+1);
            QPixmap groupOff (":/images/symbols/groups/group" + str + "off.png");
            groupVector.at(i)->setPixmap(groupOff.scaled(75, 100, Qt::KeepAspectRatio));
        }
    }


    if (currentSessionType != -1){
        for (i = 0; i < sessionVector.size(); i++){
            str = QString::number(i+1);
            if (i == currentSessionType){
                QPixmap sessionOn (":/images/symbols/sessions/session" + str + "on.png");
                sessionVector.at(i)->setPixmap(sessionOn.scaled(75,100, Qt::KeepAspectRatio));
            } else {
                QPixmap sessionOff (":/images/symbols/sessions/session" + str + "off.png");
                sessionVector.at(i)->setPixmap(sessionOff.scaled(75, 100, Qt::KeepAspectRatio));
            }
        }
    } else {
        for (i = 0; i < sessionVector.size(); i++){
            str = QString::number(i+1);
            QPixmap sessionOff (":/images/symbols/sessions/session" + str + "off.png");
            sessionVector.at(i)->setPixmap(sessionOff.scaled(75,100, Qt::KeepAspectRatio));

        }
    }


    ui->group3Screen->setNum(userSessionTime);

}

void MainWindow::toggleRecording(){
    if (sessionRunning == true){
        if (powerStatus){
            recordSession = recordSession ? false: true;
            if (recordSession){
                rec_scene->setBackgroundBrush(Qt::green);
            } else {
                rec_scene->setBackgroundBrush(Qt::white);
            }
        } else {
            recordSession = false;
            rec_scene->setBackgroundBrush(Qt::white);
        }
    } else {
        qInfo() << "No session running, cant record";
    }
}

void MainWindow::togglePowerButton(){
    if (buttonTimer.elapsed() >= 1000){
        powerStatus = powerStatus ? false: true;
        if (powerStatus) {
            qInfo() << "Machine turned on.";
            qInfo() << "battery: " + QString::number(battery);
            pi_scene->setBackgroundBrush(Qt::green);
            displayBarLevel(int(battery/12.5));
            changeConnection();
            ui->group3Screen->setNum(userSessionTime);
            updateScreen();

        } else {
            qInfo() << "Machine turned off.";
            if (sessionRunning){
                currentSession->setTimeLeft(0);
                currentSession->getTimer()->stop();
                currentSession->getTimer()->disconnect();
            }
            turnOff();
        }
    } else if (powerStatus){
        //Cycling
        currentGroup = (currentGroup == GROUP_COUNT - 1) ? 0 : ++currentGroup;
        updateScreen();
    }
}

void MainWindow::turnOff(){
    pi_scene->setBackgroundBrush(Qt::white);
    recordSession = false;
    sessionRunning = false;
    connection = -1;
    currentGroup = -1;
    currentSessionType = -1;
    currentIntensity = 0;

    displayBarLevel(0);
    updateScreen();
}

void MainWindow::softOff(){
    qInfo() << "doing softoff";
    while (currentIntensity > 0){
        displayBarSingleLight(currentIntensity);
        currentIntensity--;
        delay(1);
    }
}

void MainWindow::delay(float delayDuration){
    QTime dieTime = QTime::currentTime().addMSecs(delayDuration * 1000);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::displayBarSingleLight(int bar){
    QString str;
    for (int i = 0; i < BAR_COUNT; i++){
        if ((bar - 1) == i){
            str = QString::number(i+1);
            QPixmap numOff (":/images/symbols/bars/bar"+str+"on.png");
            barVector.at(i)->setPixmap(numOff.scaled(50, 50, Qt::KeepAspectRatio));
        } else {
            str = QString::number(i+1);
            QPixmap numOff (":/images/symbols/bars/bar"+str+"off.png");
            barVector.at(i)->setPixmap(numOff.scaled(50, 50, Qt::KeepAspectRatio));
        }
    }
}


void MainWindow::toggleIntensityUp(){
    if (powerStatus){

        if (sessionRunning){
            //change intensity
            currentIntensity++;
            if (currentIntensity > 8){
                currentIntensity = 8;
            }
            currentSession->setIntensity(currentIntensity);
            displayBarLevel(currentIntensity);
        } else {
            currentSessionType = (currentSessionType == SESSION_TYPE_COUNT-1) ? 0 : ++currentSessionType;
            updateScreen();
        }
    }
}

void MainWindow::toggleIntensityDown(){
    if (powerStatus){

        if (sessionRunning){
            //change intensity
            currentIntensity--;
            if (currentIntensity < 1){
                currentIntensity = 1;
            }
            currentSession->setIntensity(currentIntensity);
            displayBarLevel(currentIntensity);

        } else {
            currentSessionType = (currentSessionType == 0) ? SESSION_TYPE_COUNT - 1  : --currentSessionType;
            updateScreen();
        }
    }
}

void MainWindow::toggleDurationUp(){
    if (powerStatus){
        currentGroup = 2;
        userSessionTime = (userSessionTime + 5 > MAX_SESSION_LENGTH) ? MAX_SESSION_LENGTH : userSessionTime + 5;
        updateScreen();
    }
}

void MainWindow::toggleDurationDown(){
    if (powerStatus){
        currentGroup = 2;
        userSessionTime = (userSessionTime - 5 < MIN_SESSION_LENGTH) ? MIN_SESSION_LENGTH : userSessionTime - 5;
        updateScreen();
    }
}

void MainWindow::startSession(){
    qInfo() << "checking canStartSession";
    if (canStartSession()){
        //todo
        flashSelectedSession(currentSessionType);


        int duration;
        if (currentGroup == 2){
            duration = ui->group3Screen->text().toInt();
        } else if (currentGroup == 0){
            duration = 20;
        } else {
            duration = 45;
        }
        Session* ses = new Session(currentIntensity, currentSessionType, duration);

        currentSession = ses;
        sessionRunning = true;


        //start timer
        initTimer(ses->getTimer());
    } else {
        qInfo() << "cannot start session";
    }
}

void MainWindow::initTimer(QTimer* t) {

    connect(t, &QTimer::timeout, this, &MainWindow::updateTimer);

    if (connection == 2 || connection == 3) {
        t->start(1000);
    } else {
        //todo: Stop timer

        //bad connection
        qInfo() << 'Please get a better connection.';
    }

}



void MainWindow::updateTimer(){

    drainBattery();
    currentSession->decrementTimeLeft();
    qInfo() << "intensity is " << currentSession->getIntensityLvl();

    if (currentSession->getTimeLeft() == 0){
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();

        //If they want to record it, append to array. If not, skip
        if (recordSession){
            qInfo() << "Session being saved";
            sessionHistory.append(currentSession);
        }
        currentSession = nullptr;
        sessionRunning = false;
        powerStatus = false;


        softOff();
        turnOff();
    }


}

void MainWindow::drainBattery(){
    // 1 minute == 1 second
    qInfo() << "drain battery function call: ";


    // if intensity is 0, battery drains by 0.02% per second
    if (currentIntensity == 0){
        battery -= 0.02;
    // if intensity is more than 0, battery drains by intensity * 0.0347 per second
    } else {
        battery -= currentIntensity*0.0347;
    }

    if (battery < 0){
        battery = 0;
    }
    changeBattery(battery);
}

void MainWindow::changeBattery(float newBattery)
{

    if (newBattery >= 0 && newBattery <= 100){

        if (newBattery == 0.0 && powerStatus == true){
            //Turn the device off
            powerStatus = false;
            turnOff();
        } else {
            battery = newBattery;
        }

        ui->batterySpinBox->setValue(newBattery);

        //critical low 1 bar
        if (battery <= 12.5){
            //TODO
            // stop blinking 2 bar (below statement)
            //end session
            //blink for few seconds and end blinking.
        // warning 2 bar
        } else if (battery <= 25){
            // blink 2 bars
        }
    }
}

bool MainWindow::connectionTest(){

    if (connection == 1){
        MainWindow::badConnection();
        qInfo() << "bad connection";
        return false;
    } else if (connection == 2){
        MainWindow::okayConnection();
        qInfo() << "okay connection";
        return true;
    } else if (connection == 3){
        MainWindow::excellentConnection();
        qInfo() << "excellent connection";
        return true;
    }
    return false;
}

void MainWindow::badConnection(){
    QString str;
    int i;
    for (i = 0; i < barVector.size(); i++){
        str = QString::number(i+1);
        if (i < 6){
            QPixmap numOff (":/images/symbols/bars/bar" + str + "off.png");
            barVector.at(i)->setPixmap(numOff.scaled(50, 100, Qt::KeepAspectRatio));
        } else {
            QPixmap numOn (":/images/symbols/bars/bar" + str + "on.png");
            barVector.at(i)->setPixmap(numOn.scaled(50, 100, Qt::KeepAspectRatio));
        }
    }
}

void MainWindow::okayConnection(){
    QString str;
    int i;
    for (i = 0; i < barVector.size(); i++){
        str = QString::number(i+1);
        if (i > 2 && i < 6){
            QPixmap numOn (":/images/symbols/bars/bar" + str + "on.png");
            barVector.at(i)->setPixmap(numOn.scaled(50, 100, Qt::KeepAspectRatio));
        } else {
            QPixmap numOff (":/images/symbols/bars/bar" + str + "off.png");
            barVector.at(i)->setPixmap(numOff.scaled(50, 100, Qt::KeepAspectRatio));
        }
    }
}

void MainWindow::excellentConnection(){
    QString str;
    int i;
    for (i = 0; i < barVector.size(); i++){
        str = QString::number(i+1);
        if (i < 3){
            QPixmap numOn (":/images/symbols/bars/bar" + str + "on.png");
            barVector.at(i)->setPixmap(numOn.scaled(50, 100, Qt::KeepAspectRatio));
        } else {
            QPixmap numOff (":/images/symbols/bars/bar" + str + "off.png");
            barVector.at(i)->setPixmap(numOff.scaled(50, 100, Qt::KeepAspectRatio));
        }
    }
}

bool MainWindow::canStartSession(){
    if (powerStatus){
        if (currentGroup != -1 && currentSessionType != -1){
            return connectionTest();
        } else {
            qInfo() << "Session duration or session type not selected.";
            return false;
        }
    }
    return false;
}

void MainWindow::flashSelectedSession(int session){
    for (int i = 0; i < 6; i++){
        if (i % 2 == 0){
            displayBarSingleLight(session+1);
        } else {
            displayBarSingleLight(0);
        }
        delay(0.4);
    }
}

void MainWindow::changeConnection(){
    QString str = ui->connectionComboBox->currentText();
    if (str == "Bad"){
        connection = 1;
    } else if (str == "Good"){
        connection = 2;
    } else {
        connection = 3;
    }
}

void MainWindow::earConnect(){
    if (ui->leftEarComboBox->currentText() == "True" && ui->rightEarComboBox->currentText() == "True"){
        if (ui->connectionComboBox->currentText() == "Bad"){
            ui->connectionComboBox->setCurrentIndex(1);
        }
    } else {
        ui->connectionComboBox->setCurrentIndex(0);
    }
    if (powerStatus){
        if (ui->leftEarComboBox->currentText() == "True"){
            QPixmap left_CES (":/images/symbols/staticgraphics/left_CES_on.png");
            ui->left_CES_label->setPixmap(left_CES.scaled(75, 100, Qt::KeepAspectRatio));
        } else {
            QPixmap left_CES (":/images/symbols/staticgraphics/left_CES_off.png");
            ui->left_CES_label->setPixmap(left_CES.scaled(75, 100, Qt::KeepAspectRatio));
        }

        if (ui->rightEarComboBox->currentText() == "True"){
            QPixmap right_CES (":/images/symbols/staticgraphics/right_CES_on.png");
            ui->right_CES_label->setPixmap(right_CES.scaled(75, 100, Qt::KeepAspectRatio));
        } else {
            QPixmap right_CES (":/images/symbols/staticgraphics/right_CES_off.png");
            ui->right_CES_label->setPixmap(right_CES.scaled(75, 100, Qt::KeepAspectRatio));
        }
    }
}
