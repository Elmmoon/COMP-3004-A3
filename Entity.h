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
    virtual bool act(int, QVector<Log*>&) = 0; //instructs entity to act and returns what action was taken
    int getEntityID();
    bool checkEvents(int, QVector<Log*>&);
    void addEvent(SafetyEvent*);

  protected:
    int lastTimeStep;            //prevents double action in time step
    int entityID;
    QVector<SafetyEvent*> eventArr; //events are checked every time step
};

#endif
