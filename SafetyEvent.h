/*The SafetyEvent class*/

#ifndef SAFETYEVENT_H
#define SAFETYEVENT_H

#include "defs.h"
#include "Log.h"

class SafetyEvent{
  public:
    SafetyEvent(int,  int);
    ~SafetyEvent();
    int getEventType();
    int getElevatorID();
    Log* generateLog();
    static void clearEvents(QVector<SafetyEvent*>&);

  private:
    int eventType;
    int elevatorID;

};

#endif
