#include "SafetyEvent.h"

SafetyEvent::SafetyEvent(int type, int id){
    eventType = type;
    elevatorID = id;
}

SafetyEvent::~SafetyEvent(){}

Log* SafetyEvent::generateLog(){
    return new Log(elevatorID, eventType, 0, IDLE);
}

void SafetyEvent::clearEvents(QVector<SafetyEvent*>& events){
    for (auto it : events)
        delete it;
    events.clear();
}

//getters
int SafetyEvent::getEventType(){ return eventType; }
int SafetyEvent::getElevatorID(){ return elevatorID; }
