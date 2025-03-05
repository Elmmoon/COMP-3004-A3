/*The Elevator class*/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "defs.h"
#include "Log.h"
#include "Person.h"
#include "SafetyEvent.h"

class Elevator{
  public:
    Elevator(int, int);
    ~Elevator();
    bool act(int);
    void disembark(QVector<Person*>&);
    static char determineDirection(int, int);   
    char getDirection();
    char getRequestDirection();
    int getCurFloorID();
    QVector<Log*>* getLogs();
    int getElevatorID();
    void setDirection(char);
    void setCurFloorID(int);
    bool addFloorRequest(char, int);
    void addPassenger(Person*);
    void addEvent(SafetyEvent*);
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
