#ifndef PERSON_H
#define PERSON_H

#include "defs.h"

/* Class Purpose: Represents a person in the simulation
 *
 * Data Members:
 * -int personID: Unique id of this person object
 * -int curFloorID: Unique id of the floor the person is on (0 if inside elevator)
 * -int destFloorID: Unique id of the person's destination floor
 * -int requestTime: Time step of when this person requests an elevator (increments if no elevator is available)
 * -bool hasRequested: Has this person requested an elevator/floor (prevents repeated requests)
 *
 * Class Functions:
 * -Getters and Setters
 * -int act(int): Returns the person's action to the containing Floor/Elevator based on the time step
 * -bool hasArrived(): Returns if the person has arrived to their destined floor
 */

class Person{
  public:
    Person(int, int, int, int);
    ~Person();
    int act(int);
    bool hasArrived();
    int getCurFloorID();
    int getDestFloorID();
    int getRequestTime();
    bool getHasRequested();
    void setCurFloorID(int);
    void setDestFloorID(int);
    void setRequestTime(int);
    void setHasRequested(bool);

  private:
    int personID;
    int curFloorID;
    int destFloorID;
    int requestTime;
    bool hasRequested;
};

#endif
