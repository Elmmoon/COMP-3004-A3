#include "defs.h"
#include "SafetyEvent.h"

SafetyEvent::SafetyEvent(int time, int type){
    targetTimeStep = time;
    eventType = type;
    resolved = false;
}

SafetyEvent::~SafetyEvent(){}

bool SafetyEvent::act(int time, QVector<Log*>& log){
    bool isActive = (time == targetTimeStep);

    if (isActive)
        log.push_back(new Log(EVENT, eventType, ACTIVE));

    return isActive;
}

int SafetyEvent::getEventType(){
    return eventType;
}

void SafetyEvent::setAsResolved(){
    resolved = true;
}
