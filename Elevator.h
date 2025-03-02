/*The Elevator class*/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "defs.h"
#include "Log.h"
#include "Entity.h"
#include "Person.h"

class Elevator: public Entity{
  public:
    Elevator(int);
    ~Elevator();
    virtual bool act(int, QVector<Log*>&);
    char getDirection();
    void setDirection(char);
    int getCurFloorID();
    void setCurFloorID(int);
    bool addFloorRequest(char, int);
    void addPassenger(Person*);
    void disembark(QVector<Person*>&);
    static char determineDirection(int, int);
    static void resetIDCounter();

  private:
    static int nextID;
    char direction;
    int curFloorID;
    QVector <Person*> passengers;
    QVector <int> queue;          //queue of floor IDs
    void evacuate(int);             //move to safe floor if fire or power outage
    void addtoQueue(int, bool);
    void respondToPerson(Person*, Log*);

};

#endif
