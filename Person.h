/*The Person class*/

#ifndef PERSON_H
#define PERSON_H

#include <defs.h>
#include <Log.h>
#include <Entity.h>


class Person: public Entity{
  public:
    Person();
    ~Person();
    virtual vector<Log*> act(int, int);
    int getDestFloorID();
    bool getHasRequested();
    void setDestFloorID(int); //useful for fire and power outage scenarios

  private:
    int requestTime;
    bool hasRequested;
    int destFloorID;          //stores ID of floor to prevent circular reference
      
};

#endif