#include "defs.h"
#include "Floor.h"

int Floor::nextID = 1;

Floor::Floor(bool safe, Floor* below) : Entity (nextID++){
    safeFloor = safe;
    floorBelow = below;
    floorAbove = nullptr;
    requestDown = false;
    requestUp = false;
}

Floor::~Floor(){}

bool Floor::act(int time, QVector<Log*>& log){
    int logLength;
    bool logGenerated;

    logLength = log.size();

    for (auto it : personArr){
        logGenerated = it->act(time, log);
        if (logGenerated)
            respondToPerson(it, log.back());
    }
    for (auto it : elevatorArr){
        logGenerated = it->act(time, log);
        if (logGenerated)
            respondToElevator(it, log.back());
    }
    return (log.size() - logLength > 0);
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
    personArr.push_back(person);
    person->setCurFloorID(entityID);
}

void Floor::addElevator(Elevator* elevator){
    elevatorArr.push_back(elevator);
}

void Floor::removePerson(int idx){
    personArr.erase(personArr.begin() + idx);
}

void Floor::removeElevator(int idx){
    elevatorArr.erase(elevatorArr.begin() + idx);
}

 void Floor::setAbove(Floor* floor){
    floorAbove = floor;
}


bool Floor::callElevator(char direction){
    bool found = false;
    Floor* above = floorAbove;
    Floor* below = floorBelow;

    found = findElevator(direction, entityID);

    while (!found){
        if (!above and !below)
            break;
        if (above){
            found = above->findElevator(direction, entityID);
            if (found){
                break;
            }
            else
                above = above->getAbove();
        }
        if (below){
            found = below->findElevator(direction, entityID);
            if (found)
                break;
            else
                below = below->getBelow();
        }
    }

    return found;
}

bool Floor::findElevator(char direction, int floorID){
    bool found = false;

     for (auto it = elevatorArr.begin(); it != elevatorArr.end(); ++it){
         found = (*it)->addFloorRequest(direction, floorID);
         if (found)
            break;
     }

     return found;
 }

void Floor::respondToPerson(Person* person, Log* log){
    bool found;
    switch (log->getAction()){
        case CALL_UP:
            if (!requestUp){
                found = callElevator(UP);
                if (!found)
                    person->setRequestTime(person->getRequestTime() + 1);
                else
                    setRequestStatus(UP, true);
           }
            break;
        case CALL_DOWN:
            if (!requestDown){
               found = callElevator(DOWN);
               if (!found)
                    person->setRequestTime(person->getRequestTime() + 1);
                else
                    setRequestStatus(DOWN, true);
            }
            break;
    }
}

void Floor::respondToElevator(Elevator* elevator, Log* log){

    switch (log->getAction()){
        case BOARDING:
            managePersons(elevator);
            if (elevator->getDirection() == UP)
                requestUp = false;
            else if (elevator->getDirection() == DOWN)
                requestDown = false;
            break;
        case MOVE_UP:
            moveElevator(floorAbove, elevator);
            break;
        case MOVE_DOWN:
            moveElevator(floorBelow, elevator);
            break;
    }
}

void Floor::respondToEvent(Log* log){

}

void Floor::setRequestStatus(char dir, bool status){
    if (dir == UP)
        requestUp = status;
    else if (dir == DOWN)
        requestDown = status;
}

void Floor::managePersons(Elevator* elevator){
    char direction;
    QVector<Person*> disembarking;

    for (auto it = personArr.begin(); it != personArr.end(); ++it){
        if ((*it)->getHasRequested()){
            direction = Elevator::determineDirection((*it)->getCurFloorID(), (*it)->getDestFloorID());
            if (direction == elevator->getDirection() || elevator->getDirection() == IDLE){
                elevator->addPassenger(*it);
                (*it)->setCurFloorID(0);
                (*it)->setHasRequested(false);
                it = personArr.erase(it) - 1;
            }
        }
    }

    elevator->disembark(disembarking);
    for (auto it = disembarking.begin(); it != disembarking.end(); ++it)
        personArr.push_back(*it);

}

void Floor::moveElevator(Floor* floor, Elevator* elevator){
    int idx;

    idx = elevatorArr.indexOf(elevator);
    elevatorArr.erase(elevatorArr.begin() + idx);
    floor->addElevator(elevator);
    elevator->setCurFloorID(floor->getEntityID());

}

void Floor::resetIDCounter(){
    nextID = 1;
}
