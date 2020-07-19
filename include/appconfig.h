/*
 * AppConfig class
 * static member to describe the basic info about Tank App
 */
#ifndef _DF_TANKWAR_APPCONFIG_H
#define _DF_TANKWAR_APPCONFIG_H

#include "type.h"

class AppConfig {
  public:
    // games data
    static int player_nums;
    static const int max_enemy_nums;
    static const SDL_Point p1_start_point;
    static const SDL_Point p2_start_point;
    static PlayerData init_player_data(int);
    static SDL_Point enemy_start_point(int);
    static int current_level;
    static const int prepare_time;
    static const int game_ending_time;
    static const int tile_h;
    static const int tile_w;
    static const double tank_speed;
    static const double shell_speed;
    static const int max_shell;
    static const int shell_damage;
    
    // file data
    static std::string level_file_path(int);
    static std::string font_path(int);
    static std::string texture_path();

    // app data
    static SDL_Rect status_rect;
    static SDL_Rect map_rect;
    static SDL_Rect window_rect;
    static SDL_Rect logo_rect;
};

#endif // _DF_TANKWAR_APPCONFIG_H