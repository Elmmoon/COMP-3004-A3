#include "Person.h"

int Person::nextID = 1;

Person::Person(int time, int floor) : Entity (nextID++){
    requestTime = time;
    destFloorID = floor;
}

Person::~Person(){}

void Person::act(int time, int command, QVector<Log*>& log){
    log.push_back(new Log(PERSON, entityID, NOTHING));
}

int Person::getDestFloorID(){
    return destFloorID;
}

bool Person::getHasRequested(){
    return hasRequested;
}

void Person::setDestFloorID(int id){
    destFloorID = id;
}
