/*The Elevator class*/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "defs.h"
#include "Log.h"
#include "Entity.h"
#include "Person.h"
#include "Floor.h"

class Elevator: public Entity{
  public:
    Elevator(Floor*);
    ~Elevator();
    virtual void act(int, int, QVector<Log*>&);
    char getDirection();
    Floor* getCurFloor();
    void addToQueue(int);
    void addPassenger(Person*);
    static int nextID;

  private:
    char direction;
    Floor* curFloor;
    QVector <Person*> passengers;
    QVector <int> queue;          //queue of floor IDs
    void move();
    void evacuate();             //move to safe floor if fire or power outage
    
};

#endif
