//List of general definitions

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <string>
#include <QString>
#include <QVector>

using namespace std;

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
#define REMOVE_OBS  1
#define DOOR_OPEN   2
#define DOOR_CLOSE  3
#define CALL        4
#define ENTER       5
#define EXIT        6
#define EVACUTE     7
#define MOVE_UP     8
#define MOVE_DOWN   9
#define STALL       10
#define ARRIVED     11
#define WAIT        12

//Constant (miscellaneous definitions)
#define CAPACITY  3
#define UP        'U'
#define DOWN      'D'
#define LOOP_TIME 1000

#endif
