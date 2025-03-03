/*The Floor class*/

#ifndef FLOOR_H
#define FLOOR_H

#include "defs.h"
#include "Person.h"
#include "Elevator.h"


class Floor{
  public:
    Floor(int, bool, Floor*);
    ~Floor();
    virtual bool act(int, QVector<Log*>&);
    Floor* getAbove();
    Floor* getBelow();
    bool getSafety();
    void setAbove(Floor*);
    void addPerson(Person*);
    void addElevator(Elevator*);
    void removePerson(int);
    void removeElevator(int);
    void addEvent(int);
    int getFloorID();
    
  private:
    int floorID;
    bool safeFloor;              //for fire and power outage events
    Floor* floorAbove;           //useful so that elevators can move themselves
    Floor* floorBelow;
    bool requestUp;
    bool requestDown;
    void setRequestStatus(char, bool);
    QVector<Elevator*> elevatorArr;
    QVector<Person*> personArr;
    QVector<int> eventArr;
    QVector<Log*> logArr;
    bool callElevator(char);     //sends request to elevator
    bool findElevator(char, int);
    void respondToPerson(Person*, Log*);
    void moveElevator(Floor*, Elevator*);
    void managePersons(Elevator*);
    void respondToElevator(Elevator*, Log*);
    void respondToEvent(Log*);
};

#endif
