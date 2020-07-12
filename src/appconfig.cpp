/*
 * AppConfig class imple
 * contains some App Config Data 
 */ 
#include "appconfig.h"

int AppConfig::player_nums = 1;
int AppConfig::current_level = 28;
SDL_Rect AppConfig::window_rect = {0, 0, 29*16, 26*16};
SDL_Rect AppConfig::logo_rect = {20, 20, 406, 72};

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