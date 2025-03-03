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
    bool act(int, QVector<Log*>&);
    char getDirection();
    void setDirection(char);
    int getCurFloorID();
    void setCurFloorID(int);
    bool addFloorRequest(char, int);
    void addPassenger(Person*);
    void disembark(QVector<Person*>&);
    static char determineDirection(int, int);
    static void resetIDCounter();
    void addEvent(int);

  private:
    char direction;
    int elevatorID;
    int lastTimeStep;
    int curFloorID;
    QVector <Person*> passengers;
    QVector<int> eventArr;
    QVector <int> queue;          //queue of floor IDs
    void evacuate(int);             //move to safe floor if fire or power outage
    void addtoQueue(int, bool);
    void respondToPerson(Person*, Log*);

};

#endif
