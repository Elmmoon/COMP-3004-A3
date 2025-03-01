#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "defs.h"
#include "Elevator.h"
#include "Entity.h"
#include "Floor.h"
#include "Person.h"
#include "SafetyEvent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool isRunning;
    int curTimeStep;
    QTimer* timer;
    QVector<Person*> personArr;
    QVector<Floor*> floorArr;
    QVector<Elevator*> elevatorArr;
    QVector<SafetyEvent*> safetyEventArr;

private slots:
    void start();
    void pause();
    void play();
    void enterLine();
    void clearArr();
    void executeTimeStep();    //increments time step and instructs all entities to act
    void inputParam();         //input number of entities, their behaviour and events
    void toggleOn(bool);       //pause or play simulation
    void endProgram();         //stop button
    void displayLog(QVector<Log*>&);
};
#endif // MAINWINDOW_H
