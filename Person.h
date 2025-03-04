/*The Person class*/

#ifndef PERSON_H
#define PERSON_H

#include "defs.h"


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
    void setDestFloorID(int); //useful for fire and power outage scenarios
    void setRequestTime(int);
    void setHasRequested(bool);

  private:
    int personID;
    int curFloorID; //stores ID of floor to prevent circular reference
    int destFloorID;
    int requestTime;
    bool hasRequested;
};

#endif
