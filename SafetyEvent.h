/*The SafetyEvent class*/

#ifndef SAFETYEVENT_H
#define SAFETYEVENT_H

#include "defs.h"
#include "Log.h"

class SafetyEvent{
  public:
    SafetyEvent(int, int);
    ~SafetyEvent();
    bool act(int, QVector<Log*>&);
    int getEventType();
    void setAsResolved();

  private:
    int targetTimeStep;
    bool resolved; 
    int eventType; //Tells entities what event is occurring
    
};

#endif
