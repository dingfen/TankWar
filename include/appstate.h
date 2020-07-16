/*
 * AppState class
 * indicate the state of App, show what the stage is
 * base class, Game Menu etc. derived from it
 */
#ifndef _DF_TANKWAR_APPSTATE_H
#define _DF_TANKWAR_APPSTATE_H

#include <iostream>
#include <memory>
#include "appconfig.h"
#include "spriteconfig.h"
#include "exception.h"

class AppState {
public:
    virtual ~AppState() {};
    // draw thing on the screen
    void virtual draw() = 0;
    // flash the screen
    void virtual update(int) = 0;
    // process event
    void virtual event(SDL_Event*) = 0;
    // indicate whether this state finished
    bool virtual finish() = 0;
    // change the ptr in App class, point to next state
    void virtual nextstate(std::unique_ptr<AppState>&) = 0;
};


#endif // _DF_TANKWAR_APPSTATE_H
