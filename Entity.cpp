#include "defs.h"
#include "Entity.h"

Entity::Entity(int id){
    entityID = id;
    lastTimeStep = 0;
}

Entity::~Entity(){
}

int Entity::getEntityID(){
    return entityID;
}

void Entity::addEvent(SafetyEvent* event){
    eventArr.push_back(event);
}

bool Entity::checkEvents(int time, QVector<Log *>& log){
     bool isActive;
     bool logGenerated;

     for (auto it : eventArr){
         isActive = it->act(time, log);
         if (isActive)
             logGenerated = true;
     }

     return logGenerated;
 }
