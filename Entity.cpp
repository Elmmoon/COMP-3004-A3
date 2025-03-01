#include "defs.h"
#include "Entity.h"

Entity::Entity(int id){
    entityID = id;
}

Entity::~Entity(){
}

int Entity::getEntityID(){
    return entityID;
}

void Entity::addEvent(SafetyEvent* event){
    events.push_back(event);
}
