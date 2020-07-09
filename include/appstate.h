/*
 * AppState class
 * indicate the state of App, show what the stage is
 * base class, Game Menu etc. derived from it
 */
#ifndef _DF_TANKWAR_APPSTATE_H
#define _DF_TANKWAR_APPSTATE_H

#include <iostream>
#include "appconfig.h"
#include "spriteconfig.h"
#include "exception.h"

class AppState {
public:
    virtual ~AppState() {};

    void virtual draw() = 0;

    void virtual update() = 0;

    void virtual event(SDL_Event*) = 0;
};


#endif // _DF_TANKWAR_APPSTATE_H
