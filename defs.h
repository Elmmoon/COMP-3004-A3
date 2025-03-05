//List of general definitions

#ifndef DEFS_H
#define DEFS_H

//Imports
#include <QString>
#include <QVector>

//Actions (Used for Log.action and Person.act())
#define NOTHING     -1
#define IDLING      0
#define CALL        1
#define MOVE        2
#define REQUEST     3
#define BOARDING    4
#define DOOR_OPEN   5
#define DOOR_CLOSE  6
#define EVACUATE    7

//Event Types (Used for SafetyEvent.eventType and Log.action)
#define HELP        8
#define OBSTACLE    9
#define OVERLOAD    10
#define OPEN        11
#define CLOSE       12
#define POWER       13
#define FIRE        14
#define REPEAT_OBS  15

//Constant (Miscellaneous definitions)
#define UP          'U'
#define DOWN        'D'
#define IDLE        'I'
#define SAFE_FLOOR  1
#define LOOP_TIME   1500

#endif
