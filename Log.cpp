#include "defs.h"
#include "log.h"

Log::Log(int type, int id, int action){
    entityType = type;
    entityID = id;
    this->action = action;
}
Log::~Log(){}

void Log::generateLog(QString& output){
    output = "later";
}
int Log::getAction(){
    return action;
}
