/*The Person class*/

#ifndef PERSON_H
#define PERSON_H

#include "defs.h"
#include "Log.h"
#include "Entity.h"


class Person: public Entity{
  public:
    Person(int, int, int);
    ~Person();
    virtual bool act(int, QVector<Log*>&);
    int getDestFloorID();
    void setDestFloorID(int); //useful for fire and power outage scenarios
    int getCurFloorID();
    void setCurFloorID(int);
    int getRequestTime();
    bool getHasRequested();
    void setHasRequested(bool);
    void setRequestTime(int);
    bool hasArrived();
    static void resetIDCounter();

  private:
    static int nextID;
    int requestTime;
    bool hasRequested;
    int curFloorID;
    int destFloorID;          //stores ID of floor to prevent circular reference
      
};

#endif
