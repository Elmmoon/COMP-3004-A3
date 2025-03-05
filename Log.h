/*The Log class
  Used to track entity actions and inform calling 
  object on what action was taken*/

#ifndef LOG_H
#define LOG_H

#include "defs.h"

class Log{
  public:
    Log(int, int, int, char);
    ~Log();
    QString generateLog();
    int getID();
    int getAction();
    int getDirection();
    static void clearLogs(QVector<Log*>&);

  private:
    int elevatorID;
    int action;
    int floorID;
    char direction;
};

#endif
