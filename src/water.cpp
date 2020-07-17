#include "water.h"

Water::Water(double x, double y)
    : Object(x, y, SpriteType::WATER),
    flash_cycle_(0), texture_off_(0) {

}

Water::Water(SDL_Point p)
    : Object(p, SpriteType::WATER),
    flash_cycle_(0), texture_off_(0) {

}

Water::~Water() {
    
}

void Water::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect objrect = e->getSprite(type_, texture_off_);
    e->draw(objrect, SDL_Rect{x_, y_, w_, h_});
}

void Water::try_update(int dt) {
    if (flash_cycle_ < water_flicker) {
        flash_cycle_ += dt;
    } else {
        flash_cycle_ = 0;
        texture_off_ = (texture_off_+1) % 2;
    }
}