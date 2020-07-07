/*
 * App class
 * app run/pause/save operations
 */
#ifndef _DF_TANKWAR_APP_H
#define _DF_TANKWAR_APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "appconfig.h"

using std::cerr;
using std::endl;

class App {

  public:
    // App start run
    void run();
};

#endif // _DF_TANKWAR_APP_H