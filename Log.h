#ifndef LOG_H
#define LOG_H

#include "defs.h"

/* Class Purpose: Track an elevator's/event's action for display and communication purposes
 *
 * Data Members:
 * -int elevatorID: Unique id of the elevator that took action (0 if an event with no target elevator)
 * -int action: Action taken place as defined in defs.h
 * -int floorID: Unique id of the involved floor (used mainly for elevator movements and requests)
 * -char direction: Direction of the elevator (used mainly for elevator movements and requests)
 *
 * Class Functions:
 * -Getters
 * -QString generateDisplayLog(): Convert this Log into a displayable QString
 * -static void clearLogs(QVector<Log*>&): Clears vector of Log objects and deletes used memory
 */

class Log{
  public:
    Log(int, int, int, char);
    ~Log();
    int getID();
    int getAction();
    int getDirection();
    QString generateDisplayLog();
    static void clearLogs(QVector<Log*>&);

  private:
    int elevatorID;
    int action;
    int floorID;
    char direction;
};

#endif
