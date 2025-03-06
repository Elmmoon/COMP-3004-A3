#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "defs.h"
#include "Elevator.h"
#include "Floor.h"
#include "Person.h"
#include "SafetyEvent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/* Class Purpose: The main controller of the simulation and the main window GUI
 *
 * Data Members:
 * -int isRunning: Is a simulation currently running
 * -int curTimeStep: The current time step
 * -QTimer* timstarr: The timer that maintains the intervals between each time step
 * -QVector<Person*> personArr: Vector of all people in the simulation
 * -QVector<Floor*> floorArr: Vector of all floors in the simulation
 * -QVector<Elevator*> elevatorArr: Vector of all elevators in the simulation
 * -QVector<SafetyEvent*> eventQueue: Queue of inputted events to be used in the next time step
 * -QVector<Log*> eventLogArr: Vector of action logs that affect all floors (POWER and FIRE)
 *
 * Class Functions:
 * -void addEventToQueue(int, int): Generates a SafetyEvent, adds it to the queue and displays a message
 * -void distributeEvent(SafetyEvent*): Distributes the event to the corresponding floors/elevator
 * -void clearArr(): Clears the vectors and deallocates their memory
 * -void initParam(): Initializes all of the simulatione entities
 * -void displayLogs(Floor*): Displays the logs for the corresponding floor
 * -bool allPassengersArrived(): Determines if all passengers have arrived to their destintations
 *
 * Slot Functions:
 * -void start(): Starts the simulation
 * -void pause(): Pauses the simulation
 * -void play(): Resumes the simulation
 * -void executeTimeStep(): Executes the next time step
 * -void endProgram(): Ends the current simulation
 * -void addCloseEvent(): Adds a close door event to eventQueue
 * -void addOpenEvent(): Adds an open door event to eventQueue
 * -void addHelpEvent(): Adds a help button event to eventQueue
 * -void addOverloadEvent(): Adds an overload event to eventQueue
 * -void addObstacleEvent(): Adds an obstacle event to eventQueue
 * -void addFireEvent(): Adds a fire event to eventQueue
 * -void addPowerEvent(): Adds a power outage event to eventQueue
 */

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
    QVector<SafetyEvent*> eventQueue;
    QVector<Log*> eventLogArr;
    void addEventToQueue(int, int);
    void distributeEvent(SafetyEvent*);
    void clearArr();
    void initParam();
    void displayLogs(Floor*);
    bool allPassengersArrived();

private slots:
    void start();
    void pause();
    void play();
    void executeTimeStep();
    void endProgram();
    void addCloseEvent();
    void addOpenEvent();
    void addHelpEvent();
    void addOverloadEvent();
    void addObstacleEvent();
    void addFireEvent();
    void addPowerEvent();

};
#endif // MAINWINDOW_H
