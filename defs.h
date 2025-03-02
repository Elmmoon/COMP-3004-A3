//List of general definitions

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <string>
#include <QString>
#include <QVector>
#include <QDebug>

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
#define CALL_UP     1
#define CALL_DOWN   2
#define MOVE_UP     3
#define MOVE_DOWN   4
#define REQUEST     5
#define BOARDING    6
#define REMOVE_OBS  7
#define DOOR_OPEN   8
#define DOOR_CLOSE  9
#define EVACUTE     11
#define ACTIVE      13


//Constant (miscellaneous definitions)
#define CAPACITY  10
#define UP        'U'
#define DOWN      'D'
#define IDLE      'I'
#define LOOP_TIME 1000

#endif
