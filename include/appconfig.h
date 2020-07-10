/*
 * AppConfig class
 * static member to describe the basic info about Tank App
 */
#ifndef _DF_TANKWAR_APPCONFIG_H
#define _DF_TANKWAR_APPCONFIG_H

#include <SDL2/SDL.h>
#include <iostream>

class AppConfig {
  public:
    // games data
    static int player_nums;

    // app data
    static std::string font_path();
    static std::string texture_path();
    static SDL_Rect window_rect;
    static SDL_Rect logo_rect;
};

#endif // _DF_TANKWAR_APPCONFIG_H