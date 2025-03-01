#include "defs.h"
#include "SafetyEvent.h"

SafetyEvent::SafetyEvent(int time, int type){
    targetTimeStep = time;
    eventType = type;
    resolved = false;
}

SafetyEvent::~SafetyEvent(){}

Log* SafetyEvent::act(int){
    return new Log(0, 0, 0);
}

int SafetyEvent::getEventType(){
    return eventType;
}

void SafetyEvent::setAsResolved(){
    resolved = true;
}
