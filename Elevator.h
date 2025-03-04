/*The Elevator class*/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "defs.h"
#include "Log.h"
#include "Person.h"

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
    void addEvent(int);

  private:

    int elevatorID;
    int lastTimeStep;
    char direction;
    char requestDirection;
    int curFloorID;
    QVector<Person*> passengers;
    QVector<int> eventArr;
    QVector<int> queue;          //queue of floor IDs
    QVector<Log*> logArr;
    void evacuate(int);             //move to safe floor if fire or power outage
    bool addtoQueue(int, bool);
    Log* respondToPerson(Person*, int);

};

#endif
