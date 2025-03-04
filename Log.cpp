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
    QString str("           ");
    QString directionString;

    if (direction == UP)
        directionString = "up";
    else
        directionString = "down";

    switch (action){
        case CALL:
            str.append(QString("Received a request %1 from floor %2").arg(directionString).arg(floorID));
            break;
        case REQUEST:
            str.append(QString("A passenger has requested a stop to floor %1").arg(floorID));
            break;
        case BOARDING:
            str.append(QString("Opens its doors, rings a bell, allows passengers to move and then close its doors"));
            break;
        case MOVE:
            str.append(QString("Moved %1 to floor %2").arg(directionString).arg(floorID));
            break;
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
void Log::setDirection(char dir){ direction =  dir; }
