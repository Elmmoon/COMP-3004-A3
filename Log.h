/*The Log class
  Used to track entity actions and inform calling 
  object on what action was taken*/

#ifndef LOG_H
#define LOG_H

#include "defs.h"

class Log{
  public:
    Log(int, int, int);
    ~Log();
    void generateLog(QString&);
    int getAction();
    int getType();

  private:
    int entityType;
    int entityID;
    int action;
};

#endif
