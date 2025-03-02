#include "defs.h"
#include "Elevator.h"

int Elevator::nextID = 1;

Elevator::Elevator(int floorID) : Entity (nextID++){
    direction = IDLE;
    curFloorID = floorID;
}

Elevator::~Elevator(){}

bool Elevator::act(int time, QVector<Log*>& log){
    int action = NOTHING;
    int logLength;
    bool logGenerated;

    logLength = log.size();

    for (auto it: passengers){
        logGenerated = it->act(time, log);
        if (logGenerated)
            respondToPerson(it, log.back());
    }

    if (!queue.isEmpty() && curFloorID == queue.front()){
        action = BOARDING;
        queue.pop_front();
        if (queue.size() == 0)
            direction = IDLE;
    }
    else{
        if (direction == DOWN)
            action = MOVE_DOWN;
        else if (direction == UP)
            action = MOVE_UP;
    }
    if (action != NOTHING){
        log.push_back(new Log(ELEVATOR, entityID, action));
    }

    return (log.size() - logLength > 0);

}

char Elevator::getDirection(){
    return direction;
}
void Elevator::setDirection(char dir){
    direction = dir;
}

bool Elevator::addFloorRequest(char requestDirection, int floorID){
    bool accepted = false;;
    char floorDirection;

    floorDirection = determineDirection(curFloorID, floorID);

    switch (direction){
        case IDLE:
            queue.clear();
            queue.push_back(floorID);
            direction = floorDirection;
            accepted = true;
            break;
        case DOWN:
            if (floorDirection == DOWN && requestDirection == DOWN){
                addtoQueue(floorID, true);
                accepted = true;
            }
            break;
        case UP:
            if (floorDirection == UP && requestDirection == UP){
                addtoQueue(floorID, false);
                accepted = true;
            }
            break;
    }

    return accepted;
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

void Elevator::addtoQueue(int floorID, bool reversed){
    int i;

    for (i = 0; i < queue.size(); i++){
        if (floorID == queue.at(i))
            return;
        if ((floorID < queue.at(i) && !reversed)|| (floorID > queue.at(i) && reversed))
            break;
    }
    queue.insert(i, floorID);
}

void Elevator::evacuate(int safeFloor){
    queue.clear();
    queue.push_back(safeFloor);
    direction = determineDirection(curFloorID, safeFloor);
    for (auto it : passengers)
        it->setDestFloorID(safeFloor);
}

int Elevator::getCurFloorID(){
    return curFloorID;
}

void Elevator::setCurFloorID(int id){
    curFloorID = id;
}

void Elevator::respondToPerson(Person* person, Log* log){
    switch (log->getAction()){
        case REQUEST:
            addtoQueue(person->getDestFloorID(), (direction == DOWN));
            if (direction == IDLE)
                direction = determineDirection(curFloorID, queue.front());
            break;
    }
}

void Elevator::disembark(QVector<Person *>& disembarking){
    for (auto it = passengers.begin(); it != passengers.end(); ++it){
        if ((*it)->getDestFloorID() == curFloorID){
            (*it)->setCurFloorID(curFloorID);
            (*it)->setHasRequested(false);
            disembarking.push_back(*it);
            it = passengers.erase(it) - 1;
        }
    }
}

void Elevator::addPassenger(Person* person){
    passengers.push_back(person);
}

void Elevator::resetIDCounter(){
    nextID = 1;
}

