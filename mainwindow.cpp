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
    connect(ui->enterButton, SIGNAL(released()), this, SLOT(enterLine()));
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
        inputParam();
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

    curTimeStep++;
    ui->output->appendPlainText(QString("Time Step %1:").arg(curTimeStep));
    for (auto it : floorArr){
        ui->output->appendPlainText(QString("   Floor %1:").arg(it->getEntityID()));
        it->act(curTimeStep, floorLogs);
        displayLogs(floorLogs);
        floorLogs.clear();
    }
    ui->output->appendPlainText("");

    if (allPassengersArrived())
        endProgram();
}

void MainWindow::inputParam(){
    Elevator::resetIDCounter();
    Floor::resetIDCounter();
    Person::resetIDCounter();

    floorArr.push_back(new Floor(true, nullptr));
    floorArr.push_back(new Floor(false, floorArr.front()));
    floorArr.front()->setAbove(floorArr.at(1));

    personArr.push_back(new Person(1, 1, 2));
    personArr.push_back(new Person(1, 1, 2));
    personArr.push_back(new Person(1, 2, 1));

    floorArr.front()->addPerson(personArr.front());
    floorArr.front()->addPerson(personArr.at(1));
    floorArr.at(1)->addPerson(personArr.at(2));

    elevatorArr.push_back(new Elevator(2));
    elevatorArr.push_back(new Elevator(2));

    floorArr.at(1)->addElevator(elevatorArr.at(0));
    floorArr.at(1)->addElevator(elevatorArr.at(1));
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
    for (auto it = safetyEventArr.begin(); it != safetyEventArr.end(); ++it)
        delete *it;

    personArr.clear();
    floorArr.clear();
    elevatorArr.clear();
    safetyEventArr.clear();
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
