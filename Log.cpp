#include "defs.h"
#include "log.h"

Log::Log(int id, int act, int floor, char dir){
    elevatorID = id;
    action = act;
    floorID = floor;
    direction = dir;
}
Log::~Log(){}

QString Log::generateLog(){
    QString str;
    QString directionString;
    QString block("           ");

    if (direction == UP)
        directionString = "up";
    else
        directionString = "down";

    switch (action){
        case CALL:
            str.append(block).append(QString("*Received a request %1 from floor %2").arg(directionString).arg(floorID));
            break;
        case REQUEST:
            str.append(block).append(QString("*A passenger has requested a stop to floor %1").arg(floorID));
            break;
        case BOARDING:
            str.append(block).append(QString("*Opens its doors, rings a bell, allows passengers to move and then close its doors"));
            break;
        case MOVE:
            str.append(block).append(QString("*Moved %1 to floor %2").arg(directionString).arg(floorID));
            break;
        case HELP:
            str.append(block).append("*A passenger has pressed the help button\n");
            str.append(block).append("The elevator has established a voice connection to the building safety service\n");
            str.append(block).append("A 911 emergency call has been placed.");
            break;
        case OPEN:
            str.append(block).append("*A passenger has pressed the open door button\n");
            str.append(block).append("The door will open for another time step");
            break;
        case CLOSE:
            str.append(block).append("*A passenger has pressed the close door button\n");
            str.append(block).append("The door will close immediately");
            break;
        case OVERLOAD:
            str.append(block).append("*Detected cargo load exceeding the maximum\n");
            str.append(block).append("Doors open and the audio and text system notifies the passengers of the situation\n");
            str.append(block).append("A passenger removes the cargo");
            break;
        case OBSTACLE:
            str.append(block).append("*Obstacle detected while closing the doors\n");
            str.append(block).append("Doors reopen and the audio and text system notifies the passengers of the situation\n");
            str.append(block).append("A passenger removes the obstacles");
            break;
        case POWER:
            str.append("    *A power outage has occurred in the building. All elevators issue text and audio warnings \n");
            str.append("    notifying the passengers of the situation. Elevators will no longer receive requests and \n");
            str.append("    will immediately evacuate to a safe floor.");
            break;
        case FIRE:
            str.append("    *A fire has broken out in the building. All elevators issue text and audio warnings \n");
            str.append("    notifying the passengers of the situation. Elevators will no longer receive requests and \n");
            str.append("    will immediately evacuate to a safe floor.");
    }

    return str;
}

void Log::clearLogs(QVector<Log*>& logs){
    for (auto it : logs)
        delete it;
    logs.clear();
}

//getters
int Log::getAction(){ return action; }
int Log::getID(){ return elevatorID; }
int Log::getDirection(){ return direction;}
