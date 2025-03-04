//List of general definitions

#ifndef DEFS_H
#define DEFS_H

#include <QString>
#include <QVector>

//Entity Types (Log.entityType)
#define ELEVATOR 1
#define FLOOR    2
#define PERSON   3
#define EVENT    4

//Event Types (SafetyEvent.eventType)
#define HELP     5
#define DOOR_OBS 6
#define FIRE     7
#define OVERLOAD 8
#define POWER    9
#define OPEN     10
#define CLOSE    11

//Actions (use for Entity.act() and Log.action)
#define NOTHING     0
#define CALL        1
#define MOVE        2
#define REQUEST     3
#define BOARDING    4
#define REMOVE_OBS  5
#define DOOR_OPEN   6
#define DOOR_CLOSE  7
#define EVACUTE     8
#define ACTIVE      9


//Constant (miscellaneous definitions)
#define UP        'U'
#define DOWN      'D'
#define IDLE      'I'
#define LOOP_TIME 1500

#endif
