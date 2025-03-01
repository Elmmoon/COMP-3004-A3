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
    for (auto it = personArr.begin(); it != personArr.end(); ++it)
        delete *it;
    for (auto it = floorArr.begin(); it != floorArr.end(); ++it)
        delete *it;
    for (auto it = elevatorArr.begin(); it != elevatorArr.end(); ++it)
        delete *it;
    for (auto it = safetyEventArr.begin(); it != safetyEventArr.end(); ++it)
        delete *it;
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
    if (isRunning && timer->isActive())
        timer->stop();
}

void MainWindow::play(){
    if (isRunning && !timer->isActive())
        timer->start(LOOP_TIME);
}

void MainWindow::enterLine(){

}

void MainWindow::executeTimeStep(){
    QVector<Log*> floorLogs;

    curTimeStep++;
    for (auto it : floorArr)
        it->act(curTimeStep, NOTHING, floorLogs);
    displayLog(floorLogs);
}

void MainWindow::inputParam(){
    floorArr.push_back(new Floor(true, NULL));
    floorArr.push_back(new Floor(false, floorArr.front()));
    floorArr.front()->setAbove(floorArr.at(1));

    personArr.push_back(new Person(1, 2));
    personArr.push_back(new Person(1, 2));
    personArr.push_back(new Person(2, 1));

    elevatorArr.push_back(new Elevator(floorArr.front()));
    elevatorArr.push_back(new Elevator(floorArr.at(1)));

    floorArr.front()->addPerson(personArr.front());
    floorArr.front()->addPerson(personArr.at(1));
    floorArr.at(1)->addPerson(personArr.at(2));


}

void MainWindow::toggleOn(bool){

}

void MainWindow::endProgram(){
    if (isRunning){
        pause();
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
    for (auto it : safetyEventArr)
        delete it;

    personArr.clear();
    floorArr.clear();
    elevatorArr.clear();
    safetyEventArr.clear();
}

void MainWindow::displayLog(QVector<Log*>& log){
    QString qstr;
    for (auto it : log){
        it->generateLog(qstr);
        ui->output->appendPlainText(qstr);
        delete it;
    }
    log.clear();

}
