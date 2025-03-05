//List of general definitions

#ifndef DEFS_H
#define DEFS_H

#include <QString>
#include <QVector>
#include <QDebug>

//Actions (use for Entity.act() and Log.action)
#define NOTHING     0
#define CALL        1
#define MOVE        2
#define REQUEST     3
#define BOARDING    4
#define DOOR_OPEN   5
#define DOOR_CLOSE  6
#define EVACUATE    7

//Event Types (SafetyEvent.eventType)
#define HELP        8
#define OBSTACLE    9
#define OVERLOAD    10
#define OPEN        11
#define CLOSE       12
#define POWER       13
#define FIRE        14
#define REPEAT_OBS  15

//Constant (miscellaneous definitions)
#define UP          'U'
#define DOWN        'D'
#define IDLE        'I'
#define SAFE_FLOOR  1
#define LOOP_TIME   1500

#endif
