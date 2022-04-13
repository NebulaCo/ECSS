#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

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
    connect(ui->batterySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateBattery);
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

    activeQListWidget = ui->historyListView;
    activeQListWidget->addItems(sessionHistoryView);
    activeQListWidget->setCurrentRow(0);


    initalizeVectors();
    updateScreen();

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

void MainWindow::checkPress() {
    buttonTimer.restart();
}

void MainWindow::updateTreatmentHistory(){
    activeQListWidget->clear();
    activeQListWidget->addItems(sessionHistoryView);
    activeQListWidget->setCurrentRow(0);

}

void MainWindow::updateScreen(){
    int i;
    QString str;

    //if the power is off
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
        pi_scene->setBackgroundBrush(Qt::white);
        updateTreatmentHistory();
        return;
    }


    // if the power is on
    pi_scene->setBackgroundBrush(Qt::green);
    ui->group3Screen->setNum(userSessionTime);


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
}

void MainWindow::toggleRecording(){
    if (powerStatus){

    }
    if (sessionRunning == true){
        if (powerStatus){
            recordSession = recordSession ? false: true;
            if (recordSession){
                rec_scene->setBackgroundBrush(Qt::green);
            } else {
                rec_scene->setBackgroundBrush(Qt::white);
            }
        }
    } else {
        qInfo() << "No session running, cant record";
    }
}

void MainWindow::togglePowerButton(){

    if (buttonTimer.elapsed() >= 1000){
        //change power status
        powerStatus = powerStatus ? false: true;
        if (powerStatus) {
            qInfo() << "Machine turned on.";
            displayBattery();
            changeConnection();
            updateScreen();

        } else {
            turnOff();
        }
    } else if (powerStatus){
        //Cycling groups
        currentGroup = (currentGroup == GROUP_COUNT - 1) ? 0 : ++currentGroup;

    }
    updateScreen();
}

void MainWindow::displayBattery(){
    QTimer* batteryTimer = new QTimer(this);
    displayBarLevel(qCeil(battery/12.5));
    connect(batteryTimer, &QTimer::timeout, this, &MainWindow::displayEmptyBar);
    batteryTimer->start(4000);
}

void MainWindow::displayEmptyBar(){
    displayBarLevel(0);
}

void MainWindow::displayBarLevel(int bars){

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

void MainWindow::turnOff(){
    qInfo() << "Machine turned off.";

    if (sessionRunning){
        currentSession->setTimeLeft(0);
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        sessionRunning = false;
    }

    recordSession = false;
    connection = -1;
    currentGroup = -1;
    currentSessionType = -1;
    currentIntensity = 0;

    displayBarLevel(0);

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

void MainWindow::toggleIntensityUp(){
    if (powerStatus){

        if (sessionRunning){
            //change intensity
            currentIntensity++;
            if (currentIntensity > 8){
                currentIntensity = 8;
            }
            currentSession->setIntensity(currentIntensity);
            displayBarSingleLight(currentIntensity);
        } else {
            // change session type
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
            displayBarSingleLight(currentIntensity);

        } else {
            // change session type
            currentSessionType = (currentSessionType <= 0) ? SESSION_TYPE_COUNT - 1  : --currentSessionType;
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

        blinkSelectedSession(currentSessionType);
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
        initSessionTimer(ses->getTimer());
    } else {
        qInfo() << "cannot start session";
    }
}



void MainWindow::initSessionTimer(QTimer* t) {

    connect(t, &QTimer::timeout, this, &MainWindow::updateSessionTimer);

    qInfo() << "connection: " << connection;
    if (connection == 2 || connection == 3) {
        t->start(1000);
    }
}

void MainWindow::updateSessionTimer(){

    drainBattery();
    currentSession->decrementTimeLeft();
    qInfo() << "intensity is " << currentSession->getIntensityLvl();

    if (currentSession->getTimeLeft() == 0){
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();

        //If they want to record it, append to array. If not, skip
        if (recordSession){
            qInfo() << "Session being saved";
            sessionHistoryView.append(currentSession->toString());
            sessionHistory.append(currentSession);
        }
        currentSession = nullptr;
        sessionRunning = false;
        powerStatus = false;

        softOff();
        turnOff();
    }
    updateScreen();
}

void MainWindow::drainBattery(){
    // 1 minute == 1 second
    qInfo() << "drain";


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
    updateBattery(battery);
}

void MainWindow::updateBattery(float newBattery)
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

        if (powerStatus){
            if (battery <= 12.5){
                qInfo() << "blinking very low battery";
                blinkLowBattery(battery);
                blinkTimeLeft = 8;
            // warning 2 bar
            } else if (battery <= 25){
                qInfo() << "blinking low battery";
                blinkLowBattery(battery);
                blinkTimeLeft = 8;
            }
        }

    }
    updateScreen();
}

void MainWindow::blinkCESMode(){
    blinkTimer = new QTimer(this);
    connect(blinkTimer, &QTimer::timeout, this, &MainWindow::updateBlinkCESModeTimer);
    blinkTimer->start(500);
    blinkTimeLeft = 8;
}

void MainWindow::updateBlinkCESModeTimer(){

    if (blinkTimeLeft >= 0){
        if (blinkTimeLeft % 2 == 0){
            if (currentSession->getIsShortCESMode()){
                QPixmap short_CES (":/images/symbols/staticgraphics/short_CES_on.png");
                ui->short_CES_label->setPixmap(short_CES.scaled(75, 100, Qt::KeepAspectRatio));
            } else {
                QPixmap duty_CES (":/images/symbols/staticgraphics/duty_cycle_CES_on.png");
                ui->duty_CES_label->setPixmap(duty_CES.scaled(75, 100, Qt::KeepAspectRatio));
            }
        } else {
            QPixmap short_CES (":/images/symbols/staticgraphics/short_CES_off.png");
            ui->short_CES_label->setPixmap(short_CES.scaled(75, 100, Qt::KeepAspectRatio));
            QPixmap duty_CES (":/images/symbols/staticgraphics/duty_cycle_CES_off.png");
            ui->duty_CES_label->setPixmap(duty_CES.scaled(75, 100, Qt::KeepAspectRatio));
        }
    } else {
        blinkTimer->stop();
        blinkTimer->disconnect();
    }
    updateScreen();
    blinkTimeLeft--;
}

void MainWindow::blinkLowBattery(float battery){
    lowBatteryTimer = new QTimer(this);
    if (powerStatus){
        if (battery <= 25 && battery > 12.5){
            connect(lowBatteryTimer, &QTimer::timeout, this, &MainWindow::updatelowBatteryTimer);
        } else if (battery <= 12.5){
            connect(lowBatteryTimer, &QTimer::timeout, this, &MainWindow::updateCriticalLowBatteryTimer);
        }
    }

    lowBatteryTimer->start(300);
    blinkTimeLeft = 8;
}

void MainWindow::updatelowBatteryTimer(){
    if (blinkTimeLeft >= 0){
        if (blinkTimeLeft % 2 == 0){
            displayBattery();
        } else {
            displayBarLevel(0);
        }
    } else {
        lowBatteryTimer->stop();
        lowBatteryTimer->disconnect();
        //blinkTimeLeft = 8;
        displayBarLevel(0);
    }
    updateScreen();
    blinkTimeLeft--;
}

void MainWindow::updateCriticalLowBatteryTimer(){
    if (blinkTimeLeft >= 0){
        if (blinkTimeLeft % 2 == 0){
            displayBattery();
        } else {
            displayBarLevel(0);
        }
    } else {
        lowBatteryTimer->stop();
        lowBatteryTimer->disconnect();
        //blinkTimeLeft = 8;
        displayBarLevel(0);
        powerStatus = false;
        turnOff();
    }
    updateScreen();
    blinkTimeLeft--;
}

void MainWindow::blinkBadConnection(){

    blinkTimer = new QTimer(this);
    connect(blinkTimer, &QTimer::timeout, this, &MainWindow::updateBlinkTimer);
    blinkTimer->start(400);
    blinkTimeLeft = 8;
}

void MainWindow::updateBlinkTimer(){

    if (blinkTimeLeft >= 0){
        if (blinkTimeLeft % 2 == 0){
            badConnection();
        } else {
            displayBarLevel(0);
        }
    } else {
        blinkTimer->stop();
        blinkTimer->disconnect();
        //blinkTimeLeft = 8;
        displayBarLevel(0);
    }
    updateScreen();
    blinkTimeLeft--;
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

bool MainWindow::connectionTest(){

    if (connection == 1){
        qInfo() << "bad connection";
        blinkBadConnection();
        return false;
    } else if (connection == 2){
        qInfo() << "okay connection";
        MainWindow::okayConnection();
        blinkCESMode();
        updateScreen();
        return true;
    } else if (connection == 3){
        qInfo() << "excellent connection";
        MainWindow::excellentConnection();
        blinkCESMode();
        updateScreen();
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

void MainWindow::blinkSelectedSession(int session){
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
    if (sessionRunning){
        if (connection == 1){
            pauseSession();
        } else {
            resumeSession();
        }
    }
}

void MainWindow::pauseSession(){
    currentSession->getTimer()->stop();
    currentSession->setIntensity(0);
    blinkBadConnection();
    sessionPaused = true;
    qInfo() << "pausing session";
}

void MainWindow::resumeSession(){
    sessionPaused = false;
    currentSession->setIntensity(currentIntensity);
    currentSession->getTimer()->start(1000);

    qInfo() << "resuming session";
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
        changeConnection();
    }
    updateScreen();
}
