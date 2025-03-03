#include "Person.h"

int Person::nextID = 1;

Person::Person(int curFloor, int time, int destFloor) : Entity (nextID++){
    requestTime = time;
    destFloorID = destFloor;
    curFloorID = curFloor;
    hasRequested = false;
}

Person::~Person(){}

bool Person::act(int time, QVector<Log*>& log){
    int logLength;
    int action = NOTHING;

    if (time == lastTimeStep)
        return false;

    logLength = log.size();

    //event check

    if (!hasRequested){
        if (curFloorID > 0){
            if (time == requestTime && !hasArrived()){
                if (curFloorID > destFloorID)
                    action = CALL_DOWN;
                else
                    action = CALL_UP;
                hasRequested = true;
            }
        }
        else{
            action = REQUEST;
            hasRequested = true;
        }

        lastTimeStep++;
        if (action != NOTHING)
            log.push_back(new Log(PERSON, entityID, action));
    }

    return (log.size() - logLength > 0);
}

int Person::getDestFloorID(){
    return destFloorID;
}

void Person::setDestFloorID(int id){
    destFloorID = id;
}

int Person::getCurFloorID(){
    return curFloorID;
}

void Person::setCurFloorID(int id){
    curFloorID = id;
}

int Person::getRequestTime(){
    return requestTime;
}

void Person::setRequestTime(int time){
    requestTime = time;
}

bool Person::hasArrived(){
    return (curFloorID == destFloorID);
}

bool Person::getHasRequested(){
    return hasRequested;
}

void Person::setHasRequested(bool val){
    hasRequested = val;
}

void Person::resetIDCounter(){
    nextID = 1;
}
