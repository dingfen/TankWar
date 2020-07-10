/*
 * AppConfig class imple
 * contains some App Config Data 
 */ 
#include "appconfig.h"

int AppConfig::player_nums = 1;
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
