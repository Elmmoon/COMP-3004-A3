#include "defs.h"
#include "Elevator.h"

Elevator::Elevator(int id, int floorID){
    elevatorID = id;
    lastTimeStep = 0;
    direction = IDLE;
    requestDirection = IDLE;
    curFloorID = floorID;
    lastAction = NOTHING;
}

Elevator::~Elevator(){
    Log::clearLogs(logArr);
}

bool Elevator::act(int time){
    int action = NOTHING;
    int floorID;
    char actionDirection;
    int personAction;

    //skip if already acted
    if (time == lastTimeStep)
        return false;

    floorID = curFloorID;
    lastTimeStep++;

    for (auto it : eventArr)
        respondToEvent(it);

    eventArr.clear();

    //allow passengers to first make requests
    for (auto it : passengers){
        personAction = it->act(time);
        respondToPerson(it, personAction);
    }

    actionDirection = direction;

    //door open
    if (isLastActionEvent())
        action = BOARDING;
    //board passengers if arrived
    else if (!queue.isEmpty() && curFloorID == queue.front()){
        action = BOARDING;
        queue.pop_front();
        if (queue.size() == 0){
            direction = IDLE;
            actionDirection = requestDirection;
        }
    }
    else{
        if (direction == DOWN){
            action = MOVE;
            floorID--;
        }
        else if (direction == UP){
            action = MOVE;
            floorID++;
        }
    }

    if (action != NOTHING)
        logArr.push_back(new Log(elevatorID, action, floorID, actionDirection));
    setLastAction(action);

    //did any actions occur
    return (action != NOTHING);

}

char Elevator::determineDirection(int curFloor, int destFloor){
    int difference;
    char dir;

    difference = destFloor - curFloor;

    if (difference > 0)
        dir = UP;
    else if (difference < 0)
        dir = DOWN;
    else
        dir = IDLE;

    return dir;
}

void Elevator::evacuate(){
    queue.clear();
    if (!passengers.empty()){
        queue.push_back(SAFE_FLOOR);
        direction = determineDirection(curFloorID, queue.front());
    }
    else
        direction = IDLE;
    for (auto it : passengers){
        it->setDestFloorID(SAFE_FLOOR);
        it->setHasRequested(true);
    }
    lastAction = EVACUATE;
}

void Elevator::respondToPerson(Person* person, int action){
    bool accepted;

    if (action == REQUEST){
        accepted = addtoQueue(person->getDestFloorID(), (direction == DOWN));
        if (accepted){
            if (direction == IDLE){
                requestDirection = IDLE;
                direction = determineDirection(curFloorID, queue.front());
            }
            logArr.push_back(new Log(elevatorID, REQUEST, person->getDestFloorID(), direction));
        }
    }

}

void Elevator::respondToEvent(SafetyEvent* event){
    Log* log = nullptr;

    if (passengers.empty())
        return;

    switch (event->getEventType()){
        case OVERLOAD:
        case OPEN:
        case OBSTACLE:
            if (lastAction == BOARDING){
                log = new Log(elevatorID, event->getEventType(), NOTHING, IDLE);
                setLastAction(event->getEventType());
            }
            break;
        case HELP:
            log = new Log(elevatorID, event->getEventType(), NOTHING, IDLE);
            break;
        case CLOSE:
            log = new Log(elevatorID, event->getEventType(), NOTHING, IDLE);
            setLastAction(BOARDING);
            break;

    }
    if (log)
        logArr.push_back(log);

}

bool Elevator::isLastActionEvent(){
    return (lastAction == OPEN || lastAction == OBSTACLE  || lastAction == OVERLOAD);
}

void Elevator::disembark(QVector<Person*>& disembarking){
    for (auto it = passengers.begin(); it != passengers.end(); ++it){
        if ((*it)->getDestFloorID() == curFloorID){
            (*it)->setCurFloorID(curFloorID);
            (*it)->setHasRequested(false);
            disembarking.push_back(*it);
            it = passengers.erase(it) - 1;
        }
    }
}
bool Elevator::addFloorRequest(char requestDir, int floorID){
    bool accepted = false;;
    char floorDirection;

    if (requestDirection != IDLE and requestDirection != requestDir)
        return false;

    floorDirection = determineDirection(curFloorID, floorID);

    switch (direction){
        case IDLE:
            requestDirection = requestDir;
            queue.push_back(floorID);
            direction = floorDirection;
            accepted = true;
            break;
        case DOWN:
            if ((floorDirection == DOWN || floorDirection == IDLE) && requestDir == DOWN){
                addtoQueue(floorID, true);
                //accept even if in queue
                accepted = true;
            }
            break;
        case UP:
            if ((floorDirection == UP || floorDirection == IDLE) && requestDir == UP){
                addtoQueue(floorID, false);
                //accept even if in queue
                accepted = true;
            }
            break;
    }

    return accepted;
}

bool Elevator::addtoQueue(int floorID, bool reversed){
    int i;

    for (i = 0; i < queue.size(); i++){
        if (floorID == queue.at(i))
            return false;
        if ((floorID < queue.at(i) && !reversed)|| (floorID > queue.at(i) && reversed))
            break;
    }
    queue.insert(i, floorID);

    return true;
}

void Elevator::addPassenger(Person* person){
    passengers.push_back(person);
}

void Elevator::addEvent(SafetyEvent* event){
    eventArr.push_back(event);
}

void Elevator::setLastAction(int action){
    if (lastAction != EVACUATE)
        lastAction = action;
}

//getters and setters
char Elevator::getDirection(){ return direction; }
char Elevator::getRequestDirection(){ return requestDirection; }
int Elevator::getCurFloorID(){ return curFloorID; }
int Elevator::getElevatorID(){ return elevatorID; }
QVector<Log*>* Elevator::getLogs(){ return &logArr; }
void Elevator::setDirection(char dir){ direction = dir; }
void Elevator::setCurFloorID(int id){ curFloorID = id; }
