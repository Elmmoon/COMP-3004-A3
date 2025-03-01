/*The Log class
  Used to track entity actions and inform calling 
  object on what action was taken*/

#ifndef LOG_H
#define LOG_H

#include <defs.h>

class Log{
  public:
    Log();
    ~Log();
    string displayLog();
    int getAction();

  private:
    int entityType;
    int entityID;
    int action;
};

#endif