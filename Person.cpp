#include "Person.h"

Person::Person(int id, int curFloor, int destFloor, int time){
    personID = id;
    destFloorID = destFloor;
    curFloorID = curFloor;
    requestTime = time;
    hasRequested = false;
}

Person::~Person(){}

int Person::act(int time){
    int action = NOTHING;

    if (!hasRequested){
        //on floor
        if (curFloorID > 0){
            if (time == requestTime && !hasArrived()){
                action = CALL;
                hasRequested = true;
            }
        }
        //in elevator
        else{
            action = REQUEST;
            hasRequested = true;
        }
    }

    return action;
}

bool Person::hasArrived(){
    return (curFloorID == destFloorID);
}

//getters
int Person::getDestFloorID(){ return destFloorID; }
int Person::getCurFloorID(){ return curFloorID; }
int Person::getRequestTime(){ return requestTime; }
bool Person::getHasRequested(){ return hasRequested; }

//setters
void Person::setDestFloorID(int id){ destFloorID = id; }
void Person::setCurFloorID(int id){ curFloorID = id; }
void Person::setRequestTime(int time){ requestTime = time; }
void Person::setHasRequested(bool val){ hasRequested = val; }










