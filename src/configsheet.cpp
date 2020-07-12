#include "configsheet.h"
#include "engine.h"
#include "menu.h"

void ConfigSheet::draw() {
    Engine *e = Engine::getInstance();
    e->clear();
    for (int i = 0; i < lines_.size(); i++) {
        e->writeText(SDL_Point{30, 60+40*i}, lines_[i],
            SDL_Color{0xff, 0xff, 0xff, 0}, 14, 1);
    }
    e->update();
}

void ConfigSheet::update(int dt) {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());    
}

bool ConfigSheet::finish() {
    return this->is_finished_;
}

void ConfigSheet::event(SDL_Event* e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
        case SDLK_RETURN:
        case SDLK_ESCAPE:
        case SDLK_SPACE:
            this->is_finished_ = true;
            break;
        
        default:
            break;
        }
    }
}

void ConfigSheet::nextstate(std::unique_ptr<AppState>& app_state) {
    app_state.reset(new Menu());
}

ConfigSheet::ConfigSheet()
    : is_finished_(false),  
    lines_({"Author: Ding Feng", 
    "Date: 2020 July", 
    "Basic Info: df-tankwar is a tiny game developed by SDL 2.0,",
    "the resources (image, map, font etc.) are from Internet."}) {}