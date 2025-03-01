/*The control class controlling the simulation*/

#ifndef CONTROL_H
#define CONTROL_H

#include <defs.h>
#include <Floor.h>
#include <Person.h>

class Control{
  public:
    Control();
    ~Control();
    void runControl(); //Launches simulation
    
  private:
    bool isRunning;            //paused or running
    int curTimeStep; 
    vector<Log*> log;          //stores action logs of all entities during a time step
    vector<string> displayLog; //logs converted to strings for GUI display
    vector<Person*> personArr;
    vector<Floor*> floorArr;
    void executeTimeStep();    //increments time step and instructs all entities to act
    void inputParam();         //input number of entities, their behaviour and events
    void toggleOn(bool);       //pause or play simulation
    void endProgram();         //stop button
    void displayLog();         //displays log to GUI

};

#endif
