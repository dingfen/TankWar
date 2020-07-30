/*
 * AppConfig class imple
 * contains some App Config Data 
 */ 
#include "appconfig.h"

int AppConfig::player_nums = 1;
const int AppConfig::max_enemy_nums = 4;
const SDL_Point AppConfig::p1_start_point = {128, 384};
const SDL_Point AppConfig::p2_start_point = {256, 384};
int AppConfig::current_level = 1;
const int AppConfig::max_shell = 4;
const int AppConfig::prepare_time = 3000;
const int AppConfig::game_ending_time = 2000;
const int AppConfig::tile_h = 16;
const int AppConfig::tile_w = 16;
const int AppConfig::shell_damage = 25;
const double AppConfig::tank_speed = 0.08;
const double AppConfig::shell_speed = 0.23;
const int AppConfig::tank_hp = 20;
const int AppConfig::eagle_hp = 10;
const int AppConfig::brick_hp = 10;
const int AppConfig::stone_hp = 100;
PlayerData AppConfig::p1_data(0);
PlayerData AppConfig::p2_data(1);

SDL_Rect AppConfig::status_rect = {26*16, 0, 3*16, 26*16};
SDL_Rect AppConfig::map_rect = {0, 0, 26*16, 26*16};
SDL_Rect AppConfig::window_rect = {0, 0, 29*16, 26*16};
SDL_Rect AppConfig::logo_rect = {20, 20, 406, 72};


SDL_Point AppConfig::enemy_start_point(int i) {
    SDL_Point p{192*i, 0};
    return p;
}

std::string AppConfig::texture_path() {
    static std::string texture("resources/png/texture.png");
    return texture;
}

std::string AppConfig::font_path(int index) {
    static std::vector<std::string> font{"resources/font/prstartk.ttf",
        "resources/font/arialbd.ttf", "resources/font/tank_font.ttk"};
    return font.at(index);
}

std::string AppConfig::level_file_path(int stage) {
    std::string path("resources/levels/");
    return path + std::to_string(stage);
}
