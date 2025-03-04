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
    void checkEvent();
    void checkPerson(int);
    void checkElevator(int);
    QVector<Log*>* getLogs();
    
  private:
    int floorID;
    bool safeFloor;              //for fire and power outage events
    Floor* floorAbove;           //useful so that elevators can move themselves
    Floor* floorBelow;
    bool requestUp;
    bool requestDown;
    QVector<Elevator*> elevatorArr;
    QVector<Person*> personArr;
    QVector<int> eventArr;
    QVector<Log*> logArr;
    bool callElevator(char);     //sends request to elevator
    bool findElevator(char, int);
    void respondToPerson(Person*, int);
    void moveElevator(Floor*, Elevator*);
    void managePersons(Elevator*, char);
    void respondToElevator(Elevator*, Log*);
    void respondToEvent(Log*);
    void insertLogs(QVector<Log*>&);
    void insertLog(Log*);
};

#endif
