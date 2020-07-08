/*
 * AppConfig class imple
 * contains some App Config Data 
 */ 
#include "appconfig.h"


SDL_Rect AppConfig::window_rect = {0, 0, 29*16, 26*16};

std::string AppConfig::texture_path() {
    static std::string texture("resources/png/texture.png");
    return texture;
}