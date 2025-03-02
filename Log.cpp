#include "defs.h"
#include "log.h"

Log::Log(int type, int id, int act){
    entityType = type;
    entityID = id;
    action = act;
}
Log::~Log(){}

void Log::generateLog(QString& str){
    str.append("      ");
    switch (entityType){
        case PERSON:
            str.append("Person #");
            break;
        case ELEVATOR:
            str.append("Elevator #");
            break;
    }
    str.append(QString("%1 action: %2").arg(entityID).arg(action));
}

int Log::getAction(){
    return action;
}

int Log::getType(){
    return entityType;
}
