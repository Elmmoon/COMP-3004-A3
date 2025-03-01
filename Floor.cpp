#include "defs.h"
#include "Floor.h"

int Floor::nextID = 1;

Floor::Floor(bool safe, Floor* below) : Entity (nextID++){
    safeFloor = safe;
    floorBelow = below;
}

Floor::~Floor(){}

void Floor::act(int time, int command, QVector<Log*>& log){
    Log* safetyLog;
    for (auto it : events)
        safetyLog = it->act(time);
    for (auto it : persons)
        it->act(time, NOTHING, log);
    for (auto it : elevators)
        it->act(time, NOTHING, log);

}

Floor* Floor::getAbove(){
    return floorAbove;
}

Floor* Floor::getBelow(){
    return floorBelow;
}

bool Floor::getSafety(){
    return safeFloor;
}

void Floor::addPerson(Person* person){
    persons.push_back(person);
}

void Floor::addElevator(Elevator* elevator){
    elevators.push_back(elevator);
}

void Floor::removePerson(int idx){
    persons.erase(persons.begin() + idx);
}

void Floor::removeElevator(int idx){
    elevators.erase(elevators.begin() + idx);
}

 void Floor::setAbove(Floor* floor){
    floorAbove = floor;
}
