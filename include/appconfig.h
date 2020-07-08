/*
 * AppConfig class
 * static member to describe the basic info about Tank App
 */
#ifndef _DF_TANKWAR_APPCONFIG_H
#define _DF_TANKWAR_APPCONFIG_H
#include <SDL2/SDL_rect.h>
#include <iostream>

class AppConfig {
  public:
    // games data

    // app data
    static std::string texture_path();
    static SDL_Rect window_rect;
};

#endif // _DF_TANKWAR_APPCONFIG_H