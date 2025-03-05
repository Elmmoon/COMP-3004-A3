#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "defs.h"
#include "Log.h"
#include "Person.h"
#include "SafetyEvent.h"

/* Class Purpose: Represents an elevator in the simulation
 *
 * Data Members:
 * -int elevatorID: Unique id of the elevator
 * -int lastTimeStep: Time step of last action taken (prevents repeated actions)
 * -char direction: Direction of the elevator
 * -char requestDirection: Direction of the calling floor's request (which passengers to board)
 * -int curFloorID: Unique id of the floor the elevator is in
 * -int lastAction: Last action taken (Used to drive behaviour for events)
 * -QVector<Person*> passengers: Vector of people inside the elevator
 * -QVector<SafetyEvent*> eventArr: Vector of events targetting this elevator
 * -QVector<int> queue: Vector of queued floors to visit
 * -QVector<Log*> logArr: Vector of action logs for display and communication purposes
 *
 * Class Functions:
 * -Getters and Setters
 * -bool addFloorRequest(char, int): Receives a request from a floor and can either accept or reject it
 * -void addPassenger(Person*): Add a passenger to passengers vector
 * -void addEvent(SafetyEvent*): Add an event to eventArr
 * -void act(int): Checks events, instructs passengers to make requests and decides how to act
 * -void disembark(QVector<Person*>&): Outputs a list of disembarking passengers to the vector
 * -static char determineDirection(int, int): Determines which direction is a floor relative to the current
 * -void evacuate(): Evacuates in response to a fire or power outage safety event
 * -bool addtoQueue(int, bool): Adds a floor to the queue and returns if it was accepted (no duplicates)
 * -void respondToPerson(Person*, int): Performs actions in response to a person's actions
 * -void respondToEvent(SafetyEvent*): Performs actions in accordance to the event type
 * -void setLastAction(int): Sets the last action if not evacuating
 * -bool isLastActionEvent(): Checks if last action was door open, obstacle or overload
 */
class Elevator{
  public:
    Elevator(int, int);
    ~Elevator();
    char getDirection();
    char getRequestDirection();
    int getCurFloorID();
    int getElevatorID();
    QVector<Log*>* getLogs();
    void setDirection(char);
    void setCurFloorID(int);
    bool addFloorRequest(char, int);
    void addPassenger(Person*);
    void addEvent(SafetyEvent*);
    void act(int);
    void disembark(QVector<Person*>&);
    static char determineDirection(int, int);
    void evacuate();             //move to safe floor if fire or power outage

  private:
    int elevatorID;
    int lastTimeStep;
    char direction;
    char requestDirection;
    int curFloorID;
    int lastAction;
    QVector<Person*> passengers;
    QVector<SafetyEvent*> eventArr;
    QVector<int> queue;          //queue of floor IDs
    QVector<Log*> logArr;
    bool addtoQueue(int, bool);
    void respondToPerson(Person*, int);
    void respondToEvent(SafetyEvent*);
    void setLastAction(int);
    bool isLastActionEvent();

};

#endif
