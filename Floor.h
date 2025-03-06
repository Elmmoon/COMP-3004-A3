#ifndef FLOOR_H
#define FLOOR_H

#include "defs.h"
#include "Person.h"
#include "Elevator.h"

/* Class Purpose: Represents a floor in the simulation
 *
 * Data Members:
 * -int floorID: Unique id of the elevator
 * -Floor* floorAbove: Pointer to the floor above, used for moving and making requests to elevators
 * -Floor* floorBelow: Pointer to the floor below, used for moving and making requests to elevators
 * -bool requestUp: Has a request been made to elevator to go up (prevents repeated requests)
 * -bool requestDown: Has a request been made to elevator to go down (prevents repeated requests)
 * -QVector<Elevator*>: Vector of elevators on this floor
 * -QVector<Person*> personArr: Vector of people on this floor
 * -QVector<SafetyEvent*> eventArr: Vector of events that involve this floor
 * -QVector<Log*> logArr: Vector of action logs for display and communication purposes, ordered by elevatorID
 *
 * Class Functions:
 * -Getters and Setters
 * -void addPerson(Person*): Add a person to personArr
 * -void addElevator(Elevator*): Add an elevator to elevatorArr
 * -void addEvent(SafetyEvent*): Add an event to eventArr
 * -void removePerson(Person*): Remove a person from personArr
 * -void removeElevator(Elevator*): Remove an elevator from elevatorArr
 * -void checkEvent(): Checks on each event and responds accordingly
 * -void checkPerson(int): Instructs all people on this floor to act
 * -void checkElevator(int): Instructs all elevators on this floor to act
 * -void callElevator(): Calls for an elevator for the given direction
 * -void findElevator(char, int): Finds an available elevator on the current floor
 * -void moveElevator(Floor*, Elevator*): Moves the given elevator in the given direction
 * -void respondToPerson(Person*, int): Performs actions in response to a person's actions
 * -void respondToElevator(Elevator*): Performs actions in response to the elevator's actions
 * -void insertLogArr(QVector<Log*>&): Inserts a vector of logs into logArr in order
 * -void insertLog(Log*): Wrapper for insertLogArr(QVector<Log*>&) to insert a single log
 */

class Floor{
  public:
    Floor(int, Floor*);
    ~Floor();
    Floor* getAbove();
    Floor* getBelow();
    QVector<Log*>* getLogs();
    int getFloorID();
    void setAbove(Floor*);
    void addPerson(Person*);
    void addElevator(Elevator*);
    void addEvent(SafetyEvent*);
    void removePerson(int);
    void removeElevator(int);
    void checkEvent();
    void checkPerson(int);
    void checkElevator(int);

  private:
    int floorID;
    Floor* floorAbove;           //useful so that elevators can move themselves
    Floor* floorBelow;
    bool requestUp;
    bool requestDown;
    QVector<Elevator*> elevatorArr;
    QVector<Person*> personArr;
    QVector<SafetyEvent*> eventArr;
    QVector<Log*> logArr;
    bool callElevator(char);     //sends request to elevator
    bool findElevator(char, int);
    void moveElevator(Floor*, Elevator*);
    void managePersons(Elevator*, char);
    void respondToPerson(Person*, int);
    void respondToElevator(Elevator*, Log*);
    void insertLogArr(QVector<Log*>&);
    void insertLog(Log*);
};

#endif
