/*The Person class*/

#ifndef PERSON_H
#define PERSON_H

#include "defs.h"
#include "Log.h"
#include "Entity.h"


class Person: public Entity{
  public:
    Person(int, int);
    ~Person();
    virtual void act(int, int, QVector<Log*>&);
    int getDestFloorID();
    bool getHasRequested();
    void setDestFloorID(int); //useful for fire and power outage scenarios
    static int nextID;

  private:
    int requestTime;
    bool hasRequested;
    int destFloorID;          //stores ID of floor to prevent circular reference
      
};

#endif
