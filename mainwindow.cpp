#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(released()), this, SLOT(start()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(endProgram()));
    connect(ui->pauseButton, SIGNAL(released()), this, SLOT(pause()));
    connect(ui->playButton, SIGNAL(released()), this, SLOT(play()));
    //connect(ui->enterButton, SIGNAL(released()), this, SLOT(enterLine()));
    connect(timer, &QTimer::timeout, this, &MainWindow::executeTimeStep);

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
        ui->output->clear();
        initParam();
        executeTimeStep();
        timer->start(LOOP_TIME);
    }
}

void MainWindow::pause(){
    if (isRunning && timer->isActive()){
        ui->output->appendPlainText("Simulation Paused\n");
        timer->stop();
    }
}

void MainWindow::play(){
    if (isRunning && !timer->isActive()){
        ui->output->appendPlainText("Simulation Resumed\n");
        timer->start(LOOP_TIME);
    }
}

void MainWindow::enterLine(){

}

void MainWindow::executeTimeStep(){
    QVector<Log*> floorLogs;
    bool generatedLog;

    ui->timerDisplay->setText(QString::number(++curTimeStep));
    ui->output->appendPlainText(QString("Time Step %1:").arg(curTimeStep));
    for (auto it : floorArr){
        generatedLog = it->act(curTimeStep, floorLogs);
        if (generatedLog){
            ui->output->appendPlainText(QString("   Floor %1:").arg(it->getFloorID()));
            displayLogs(floorLogs);
        }
        floorLogs.clear();
    }
    ui->output->appendPlainText("");

    if (allPassengersArrived())
        endProgram();
}

void MainWindow::initParam(){
    Floor* prevFloor;
    int initialFloorID;
    int requestTime;
    int destFloorID;


    //init base floor (safe floor)
    floorArr.push_back(new Floor(1, true, nullptr));
    prevFloor = floorArr.front();

    //init other floors
    for (int i = 2; i <= 5; i++){
        floorArr.push_back(new Floor(i, false, prevFloor));
        prevFloor->setAbove(floorArr.back());
        prevFloor = floorArr.back();
    }

    //init people from GUI inputs
    initialFloorID = ui->personInitInput1->value();
    requestTime = ui->personReqInput1->value();
    destFloorID = ui->personTarInput1->value();
    personArr.push_back(new Person(1, initialFloorID, requestTime, destFloorID));
    floorArr.at(initialFloorID - 1)->addPerson(personArr.back());

    initialFloorID = ui->personInitInput2->value();
    requestTime = ui->personReqInput2->value();
    destFloorID = ui->personTarInput2->value();
    personArr.push_back(new Person(2, initialFloorID, requestTime, destFloorID));
    floorArr.at(initialFloorID - 1)->addPerson(personArr.back());

    initialFloorID = ui->personInitInput3->value();
    requestTime = ui->personReqInput3->value();
    destFloorID = ui->personTarInput3->value();
    personArr.push_back(new Person(3, initialFloorID, requestTime, destFloorID));
    floorArr.at(initialFloorID - 1)->addPerson(personArr.back());

    //init elevators
    initialFloorID = ui->elevatorInput1->value();
    elevatorArr.push_back(new Elevator(1, initialFloorID));
    floorArr.at(initialFloorID - 1)->addElevator(elevatorArr.back());

    initialFloorID = ui->elevatorInput2->value();
    elevatorArr.push_back(new Elevator(2, initialFloorID));
    floorArr.at(initialFloorID - 1)->addElevator(elevatorArr.back());
}

void MainWindow::toggleOn(bool){

}

void MainWindow::endProgram(){
    QString str("Simulation ");

    if (sender() == ui->stopButton)
        str.append("Terminated");
    else
        str.append("Completed");

    if (isRunning){
        ui->output->appendPlainText(str);
        timer->stop();
        clearArr();
        curTimeStep = 0;
        isRunning = false;
    }
}

void MainWindow::clearArr(){

    for (auto it = personArr.begin(); it != personArr.end(); ++it)
        delete *it;
    for (auto it = floorArr.begin(); it != floorArr.end(); ++it)
        delete *it;
    for (auto it = elevatorArr.begin(); it != elevatorArr.end(); ++it)
        delete *it;

    personArr.clear();
    floorArr.clear();
    elevatorArr.clear();
    eventQueue.clear();
}

void MainWindow::displayLogs(QVector<Log*>& log){
    QString qstr;
    for (auto it : log){
        qstr.clear();
        it->generateLog(qstr);
        ui->output->appendPlainText(qstr);
        delete it;
    }
    log.clear();

}

bool MainWindow::allPassengersArrived(){
    bool arrived = true;

    for (auto it = personArr.begin(); it != personArr.end(); ++it){
        arrived = ((*it)->getCurFloorID() == (*it)->getDestFloorID());
        if (!arrived)
            break;
    }

    return arrived;
}
