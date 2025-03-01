/*The Floor class*/

#ifndef FLOOR_H
#define FLOOR_H

#include "defs.h"
#include "Person.h"

class Elevator;

class Floor: public Entity{
  public:
    Floor(bool, Floor*);
    ~Floor();
    virtual void act(int, int, QVector<Log*>&);
    Floor* getAbove();
    Floor* getBelow();
    bool getSafety();
    void setAbove(Floor*);
    void addPerson(Person*);
    void addElevator(Elevator*);
    void removePerson(int);
    void removeElevator(int);
    static int nextID;
    
  private:
    bool safeFloor;              //for fire and power outage events
    Floor* floorAbove;           //useful so that elevators can move themselves
    Floor* floorBelow;
    QVector<Elevator*> elevators;
    QVector<Person*> persons;
    void callElevator(char);     //sends request to elevator
};

#endif
