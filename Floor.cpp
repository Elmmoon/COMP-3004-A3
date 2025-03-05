#include "defs.h"
#include "Floor.h"

Floor::Floor(int id, Floor* below){
    floorID = id;
    floorBelow = below;
    floorAbove = nullptr;
    requestDown = false;
    requestUp = false;
}

Floor::~Floor(){
    Log::clearLogs(logArr);
}

void Floor::checkEvent(){
    Log::clearLogs(logArr);

    for (auto it : eventArr){
        if (it->getEventType() == FIRE || it->getEventType() == POWER){
            for (auto itx : elevatorArr)
                itx->evacuate();
            for (auto itx : personArr){
                itx->setDestFloorID(floorID);
                itx->setHasRequested(false);
            }
        }
    }
}

void Floor::checkPerson(int time){
    int action;

    for (auto it : personArr){
        action = it->act(time);
        respondToPerson(it, action);
    }
}

void Floor::checkElevator(int time){
    QVector<Log*>* elevatorLogs = nullptr;

    for (auto it : elevatorArr){
        it->act(time);
        elevatorLogs = it->getLogs();
        if (!elevatorLogs->empty()){
            respondToElevator(it, elevatorLogs->back());
            insertLogArr(*elevatorLogs);
        }
    }
}

void Floor::addPerson(Person* person){
    personArr.push_back(person);
    person->setCurFloorID(floorID);
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

bool Floor::callElevator(char direction){
    bool found = false;
    Floor* above = floorAbove;
    Floor* below = floorBelow;

    //find elevators on current floor
    found = findElevator(direction, floorID);

    while (!found){
        //no more floors to check
        if (!above and !below)
            break;
        //check floor above
        if (above){
            found = above->findElevator(direction, floorID);
            if (found){
                break;
            }
            else
                above = above->getAbove();
        }
        //check floor below
        if (below){
            found = below->findElevator(direction, floorID);
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
    //check all elevators on floor
    for (auto it : elevatorArr){
        found = it->addFloorRequest(direction, floorID);
        if (found){
            insertLog(new Log(it->getElevatorID(), CALL, floorID, direction));
            break;
        }
    }

     return found;
 }

void Floor::respondToPerson(Person* person, int action){
    bool found;
    char direction;

    //request an elevator
    if (action == CALL){
        direction = Elevator::determineDirection(person->getCurFloorID(), person->getDestFloorID());

        switch (direction){
            case UP:
                //make sure request isn't already made
                if (!requestUp){
                    found = callElevator(UP);
                    if (found)
                        requestUp = true;
                    else
                        person->setRequestTime(person->getRequestTime() + 1);
               }
                break;
            case DOWN:
                //make sure request isn't already made
                if (!requestDown){
                   found = callElevator(DOWN);
                   if (found)
                       requestDown = true;
                   else
                       person->setRequestTime(person->getRequestTime() + 1);
                }
                break;
        }
    }
}

void Floor::respondToElevator(Elevator* elevator, Log* log){

    switch (log->getAction()){

        case BOARDING:
            //move people in and out
            managePersons(elevator, log->getDirection());
            if (log->getDirection() == UP)
                requestUp = false;
            else if (log->getDirection() == DOWN)
                requestDown = false;
            break;
        case MOVE:
            if (log->getDirection() == UP)
                moveElevator(floorAbove, elevator);
            else
                moveElevator(floorBelow, elevator);
            break;
    }
}

void Floor::managePersons(Elevator* elevator, char elevatorDirection){
    char direction;
    QVector<Person*> disembarking;

    for (auto it = personArr.begin(); it != personArr.end(); ++it){
        //only move people that have made requests
        if ((*it)->getHasRequested()){
            direction = Elevator::determineDirection((*it)->getCurFloorID(), (*it)->getDestFloorID());
            //move people that going in the same direction
            if (direction == elevatorDirection || elevatorDirection == IDLE){
                elevator->addPassenger(*it);
                (*it)->setCurFloorID(0);
                (*it)->setHasRequested(false);
                it = personArr.erase(it) - 1;
            }
        }
    }

    elevator->disembark(disembarking);
    for (auto it : disembarking)
        personArr.push_back(it);

}

void Floor::moveElevator(Floor* floor, Elevator* elevator){
    int idx;

    idx = elevatorArr.indexOf(elevator);
    elevatorArr.erase(elevatorArr.begin() + idx);
    floor->addElevator(elevator);
    elevator->setCurFloorID(floor->getFloorID());

}

void Floor::insertLogArr(QVector<Log *>& logs){
    int i;

    for (i = 0; i < logArr.size(); i++){
        if (logs.front()->getID() < logArr.at(i)->getID())
            break;
    }
    for (int x = 0; x < logs.size(); x++)
        logArr.insert(i+x, logs.at(x));

    logs.clear();
}

void Floor::insertLog(Log* log){
    QVector<Log*> logs;
    logs.push_back(log);
    insertLogArr(logs);
}

void Floor::addEvent(SafetyEvent* event){
    eventArr.push_back(event);
}

//getters and setters
int Floor::getFloorID(){ return floorID; }
Floor* Floor::getAbove(){ return floorAbove; }
Floor* Floor::getBelow(){ return floorBelow; }
QVector<Log*>* Floor::getLogs(){ return &logArr; }
void Floor::setAbove(Floor* floor){ floorAbove = floor; }



