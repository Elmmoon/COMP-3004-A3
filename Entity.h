/*The Entity class
  Includes Person, Elevator and Floor */

#ifndef ENTITY_H
#define ENTITY_H

#include <defs.h>
#include <Log.h>
#include <SafetyEvent.h>

class Entity{
  public:
    Entity();
    ~Entity();
    virtual vector<Log*> act(int, int); //instructs entity to act and returns what action was taken
    int getEntityID();
    void addEvent(SafetyEvent*);

  private:
    int lastTimeStep;            //prevents double action in time step
    int entityID;
    vector<Log*> log;
    vector<SafetyEvent*> events; //events are checked every time step
};

#endif