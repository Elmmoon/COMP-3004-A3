#ifndef SAFETYEVENT_H
#define SAFETYEVENT_H

#include "defs.h"
#include "Log.h"

/* Class Purpose: Represents the safety events inputted by the user and their relevant information
 *
 * Data Members:
 * -int eventType: Type of event coded as constants in defs.h
 * -int elevatorID: Target elevator id (0 represents event that does not target an elevator)
 *
 * Class Functions:
 * -Getters
 * -Log* generateLog(): Converts SafetyEvent to a Log for display purposes
 * -static void clearEvents(QVector<SafetyEvent*>&): Clears vector of SafetyEvents and deletes used memory
 */

class SafetyEvent{
  public:
    SafetyEvent(int, int);
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
