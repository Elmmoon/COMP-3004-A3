/*The Elevator class*/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <defs.h>
#include <Log.h>
#include <Entity.h>
#include <Person.h>
#include <Floor.h>

class Elevator: public Entity{
  public:
    Elevator();
    ~Elevator();
    virtual vector<Log*> act(int, int);
    char getDirection();
    Floor* getCurFloor();
    void addToQueue(int);
    void addPassenger(Person*);

  private:
    char direction;
    Floor* curFloor;
    vector <Person*> passengers;
    vector <int> queue;          //queue of floor IDs
    void move();
    void evacuate();             //move to safe floor if fire or power outage
    
};

#endif