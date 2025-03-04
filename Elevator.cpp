#include "defs.h"
#include "Elevator.h"

Elevator::Elevator(int id, int floorID){
    elevatorID = id;
    lastTimeStep = 0;
    direction = IDLE;
    requestDirection = IDLE;
    curFloorID = floorID;
}

Elevator::~Elevator(){
    Log::clearLogs(logArr);
}

bool Elevator::act(int time){
    int action = NOTHING;
    int floorID;
    char actionDirection;
    int personAction;
    Log* log = nullptr;

    //skip if already acted
    if (time == lastTimeStep)
        return false;

    floorID = curFloorID;
    lastTimeStep++;

    //allow passengers to first make requests
    for (auto it: passengers){
        personAction = it->act(time);
        log = respondToPerson(it, personAction);
        if (log)
            logArr.push_back(log);
    }

    actionDirection = direction;

    //board passengers if arrived
    if (!queue.isEmpty() && curFloorID == queue.front()){
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

    if (action != NOTHING){
        logArr.push_back(new Log(elevatorID, action, floorID, actionDirection));
    }

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

void Elevator::evacuate(int safeFloor){
    queue.clear();
    queue.push_back(safeFloor);
    direction = determineDirection(curFloorID, safeFloor);
    for (auto it : passengers)
        it->setDestFloorID(safeFloor);
}

Log* Elevator::respondToPerson(Person* person, int action){
    Log* log = nullptr;
    bool accepted;

    if (action == REQUEST){
        accepted = addtoQueue(person->getDestFloorID(), (direction == DOWN));
        if (accepted){
            if (direction == IDLE){
                requestDirection = IDLE;
                direction = determineDirection(curFloorID, queue.front());
            }
            log = new Log(elevatorID, REQUEST, person->getDestFloorID(), direction);
        }
    }

    return log;
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

//getters and setters
char Elevator::getDirection(){ return direction; }
char Elevator::getRequestDirection(){ return requestDirection; }
int Elevator::getCurFloorID(){ return curFloorID; }
int Elevator::getElevatorID(){ return elevatorID; }
QVector<Log*>* Elevator::getLogs(){ return &logArr; }
void Elevator::setDirection(char dir){ direction = dir; }
void Elevator::setCurFloorID(int id){ curFloorID = id; }
