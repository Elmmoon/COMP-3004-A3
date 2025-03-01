/*The Entity class
  Includes Person, Elevator and Floor */

#ifndef ENTITY_H
#define ENTITY_H

#include <defs.h>
#include <Log.h>
#include <SafetyEvent.h>

class Entity{
  public:
    Entity(int);
    virtual ~Entity();
    virtual void act(int, int, QVector<Log*>&) = 0; //instructs entity to act and returns what action was taken
    int getEntityID();
    void addEvent(SafetyEvent*);

  protected:
    int lastTimeStep;            //prevents double action in time step
    int entityID;
    QVector<Log*> log;
    QVector<SafetyEvent*> events; //events are checked every time step
};

#endif
