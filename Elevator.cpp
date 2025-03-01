#include "defs.h"
#include "Elevator.h"

int Elevator::nextID = 1;

Elevator::Elevator(Floor* current) : Entity (nextID++){
    curFloor = current;
}

Elevator::~Elevator(){

}

void Elevator::act(int time, int command, QVector<Log*>& log){
    log.push_back(new Log(ELEVATOR, entityID, NOTHING));
}

char Elevator::getDirection(){
    return direction;
}

Floor* Elevator::getCurFloor(){
    return curFloor;
}

void Elevator::addToQueue(int){

}

void Elevator::move(){

}

void Elevator::evacuate(){

}

