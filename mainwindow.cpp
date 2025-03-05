#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::executeTimeStep);

    //control buttons
    connect(ui->startButton, SIGNAL(released()), this, SLOT(start()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(endProgram()));
    connect(ui->pauseButton, SIGNAL(released()), this, SLOT(pause()));
    connect(ui->playButton, SIGNAL(released()), this, SLOT(play()));

    //event buttons
    connect(ui->closeButton1, SIGNAL(released()), this, SLOT(addCloseEvent()));
    connect(ui->openButton1, SIGNAL(released()), this, SLOT(addOpenEvent()));
    connect(ui->helpButton1, SIGNAL(released()), this, SLOT(addHelpEvent()));
    connect(ui->obstacleButton1, SIGNAL(released()), this, SLOT(addObstacleEvent()));
    connect(ui->overloadButton1, SIGNAL(released()), this, SLOT(addOverloadEvent()));

    connect(ui->closeButton2, SIGNAL(released()), this, SLOT(addCloseEvent()));
    connect(ui->openButton2, SIGNAL(released()), this, SLOT(addOpenEvent()));
    connect(ui->helpButton2, SIGNAL(released()), this, SLOT(addHelpEvent()));
    connect(ui->obstacleButton2, SIGNAL(released()), this, SLOT(addObstacleEvent()));
    connect(ui->overloadButton2, SIGNAL(released()), this, SLOT(addOverloadEvent()));

    connect(ui->powerButton, SIGNAL(released()), this, SLOT(addPowerEvent()));
    connect(ui->fireButton, SIGNAL(released()), this, SLOT(addFireEvent()));

    isRunning = false;
    curTimeStep = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    clearArr();
}

void MainWindow::start(){
    if (!isRunning){
        isRunning = true;
        curTimeStep = 0;
        ui->timerDisplay->setText(QString::number(0));
        ui->logDisplay->setPlainText("Simulation Started\n");
        initParam();
        timer->start(LOOP_TIME);
    }
}

void MainWindow::pause(){
    if (isRunning && timer->isActive()){
        ui->logDisplay->appendPlainText("Simulation Paused\n");
        timer->stop();
    }
}

void MainWindow::play(){
    if (isRunning && !timer->isActive()){
        ui->logDisplay->appendPlainText("Simulation Resumed\n");
        timer->start(LOOP_TIME);
    }
}

void MainWindow::executeTimeStep(){
    QVector<QString> floorLogs;

    ui->timerDisplay->setText(QString::number(++curTimeStep));
    ui->logDisplay->appendPlainText(QString("Time Step %1:").arg(curTimeStep));

    for (auto it : eventQueue)
        distributeEvent(it);

    for (auto it : floorArr)
        it->checkEvent();
    for (auto it : floorArr)
        it->checkPerson(curTimeStep);
    for (auto it : floorArr)
        it->checkElevator(curTimeStep);

    for (auto it : eventLogArr)
        ui->logDisplay->appendPlainText(it->generateDisplayLog());
    for (auto it : floorArr)
        displayLogs(it);

    ui->logDisplay->appendPlainText("");

    Log::clearLogs(eventLogArr);
    SafetyEvent::clearEvents(eventQueue);

    if (allPassengersArrived())
        endProgram();
}

void MainWindow::initParam(){
    Floor* prevFloor = nullptr;
    int initialFloorID;
    int requestTime;
    int destFloorID;

    //init other floors
    for (int i = 1; i <= 5; i++){
        floorArr.push_back(new Floor(i, prevFloor));
        if (prevFloor)
            prevFloor->setAbove(floorArr.back());
        prevFloor = floorArr.back();
    }

    //init people from GUI inputs
    initialFloorID = ui->personInitInput1->value();
    requestTime = ui->personReqInput1->value();
    destFloorID = ui->personTarInput1->value();
    personArr.push_back(new Person(1, initialFloorID, destFloorID, requestTime));
    floorArr.at(initialFloorID - 1)->addPerson(personArr.back());

    initialFloorID = ui->personInitInput2->value();
    requestTime = ui->personReqInput2->value();
    destFloorID = ui->personTarInput2->value();
    personArr.push_back(new Person(2, initialFloorID, destFloorID, requestTime));
    floorArr.at(initialFloorID - 1)->addPerson(personArr.back());

    initialFloorID = ui->personInitInput3->value();
    requestTime = ui->personReqInput3->value();
    destFloorID = ui->personTarInput3->value();
    personArr.push_back(new Person(3, initialFloorID, destFloorID, requestTime));
    floorArr.at(initialFloorID - 1)->addPerson(personArr.back());

    //init elevators
    initialFloorID = ui->elevatorInput1->value();
    elevatorArr.push_back(new Elevator(1, initialFloorID));
    floorArr.at(initialFloorID - 1)->addElevator(elevatorArr.back());

    initialFloorID = ui->elevatorInput2->value();
    elevatorArr.push_back(new Elevator(2, initialFloorID));
    floorArr.at(initialFloorID - 1)->addElevator(elevatorArr.back());
}

void MainWindow::endProgram(){
    QString str("Simulation ");

    if (sender() == ui->stopButton)
        str.append("Terminated");
    else
        str.append("Completed");

    if (isRunning){
        ui->logDisplay->appendPlainText(str);
        timer->stop();
        clearArr();
        curTimeStep = 0;
        isRunning = false;
    }
}

void MainWindow::clearArr(){
    for (auto it : personArr)
        delete it;
    for (auto it : floorArr)
        delete it;
    for (auto it : elevatorArr)
        delete it;

    personArr.clear();
    floorArr.clear();
    elevatorArr.clear();

    Log::clearLogs(eventLogArr);
    SafetyEvent::clearEvents(eventQueue);
}

void MainWindow::displayLogs(Floor* floor){
    QVector<Log*>* logs = floor->getLogs();
    int lastID = 0;

    if (logs->size() > 0){
        ui->logDisplay->appendPlainText(QString("   Floor %1:").arg(floor->getFloorID()));
        for (auto it : *logs){
            if (it->getID() != lastID){
                ui->logDisplay->appendPlainText(QString("       Elevator %1:").arg(it->getID()));
                lastID = it->getID();
            }
            ui->logDisplay->appendPlainText(it->generateDisplayLog());
            delete it;
        }
    }

    logs->clear();
}

bool MainWindow::allPassengersArrived(){
    bool arrived = true;

    for (auto it : personArr){
        arrived = (it->getCurFloorID() == it->getDestFloorID());
        if (!arrived)
            break;
    }

    return arrived;
}

void MainWindow::addCloseEvent(){
    int elevatorID;

    if (sender() == ui->closeButton1)
        elevatorID = 1;
    else
        elevatorID = 2;

    addEventToQueue(CLOSE, elevatorID);
}

void MainWindow::addOpenEvent(){
    int elevatorID;

    if (sender() == ui->openButton1)
        elevatorID = 1;
    else
        elevatorID = 2;

    addEventToQueue(OPEN, elevatorID);
}

void MainWindow::addHelpEvent(){
    int elevatorID;

    if (sender() == ui->helpButton1)
        elevatorID = 1;
    else
        elevatorID = 2;

    addEventToQueue(HELP, elevatorID);
}

void MainWindow::addOverloadEvent(){
    int elevatorID;

    if (sender() == ui->overloadButton1)
        elevatorID = 1;
    else
        elevatorID = 2;

    addEventToQueue(OVERLOAD, elevatorID);
}

void MainWindow::addObstacleEvent(){
    int elevatorID;

    if (sender() == ui->obstacleButton1)
        elevatorID = 1;
    else
        elevatorID = 2;

    addEventToQueue(OBSTACLE, elevatorID);
}

void MainWindow::addFireEvent(){
    addEventToQueue(FIRE, 0);
}

void MainWindow::addPowerEvent(){
    addEventToQueue(POWER, 0);

}

void MainWindow::distributeEvent(SafetyEvent* event){
    if (event->getElevatorID() == 0){
        for (auto it : floorArr)
            it->addEvent(event);
        eventLogArr.push_back(new Log(event->getElevatorID(), event->getEventType(), NOTHING, IDLE));
    }
    else
        elevatorArr.at(event->getElevatorID() - 1)->addEvent(event);
}

void MainWindow::addEventToQueue(int eventType, int elevatorID){
    QString str;

    if (isRunning){
        switch (eventType){
            case OPEN:
                str = QString("A open door event has been queued for elevator %1").arg(elevatorID);
                break;
            case CLOSE:
                str = QString("A close door event has been queued for elevator %1").arg(elevatorID);
                break;
            case HELP:
                str = QString("A help event has been queued for elevator %1").arg(elevatorID);
                break;
            case OVERLOAD:
                str = QString("An overload event has been queued for elevator %1").arg(elevatorID);
                break;
            case OBSTACLE:
                str = QString("A door obstacle event has been queued for elevator %1").arg(elevatorID);
                break;
            case FIRE:
                str = QString("A fire event has been queued");
                break;
            case POWER:
                str = QString("A power outage event has been queued");
                break;
        }
        eventQueue.push_back(new SafetyEvent(eventType, elevatorID));
        ui->logDisplay->appendPlainText(str);
    }
}

