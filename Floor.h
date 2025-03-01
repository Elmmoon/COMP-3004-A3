/*The Floor class*/

#ifndef FLOOR_H
#define FLOOR_H

#include <defs.h>
#include <Person.h>

class Elevator;

class Floor: public Entity{
  public:
    Floor();
    ~Floor();
    virtual vector<Log*> act(int, int);
    Floor* getAbove();
    Floor* getBelow();
    bool getSafety();
    void addPerson(Person*);
    void addElevator(Elevator*);
    void removeElevator(int);
    
  private:
    bool safeFloor;              //for fire and power outage events
    Floor* floorAbove;           //useful so that elevators can move themselves
    Floor* floorBelow;
    vector<Elevator*> elevators;
    vector<Person*> persons;
    void callElevator(char);     //sends request to elevator
};

#endif