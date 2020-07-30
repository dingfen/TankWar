#include "bonus.h"

Bonus::Bonus(double x, double y, SpriteType type)
    : Object(x, y, type), is_destroyed_(false),
    flash_cycle_(100), keep_time_(15000) {
    w_ = 32;
    h_ = 32;
    is_display_ = true;
}

Bonus::Bonus(SDL_Point p, SpriteType type)
    : Object(p, type), is_destroyed_(false),
    flash_cycle_(100), keep_time_(15000) {
    w_ = 32;
    h_ = 32;
    is_display_ = true;
}

Bonus::~Bonus() {
    
}

bool Bonus::is_destroy() {
    return is_destroyed_;
}

void Bonus::destroy() {
    is_destroyed_ = true;
}

void Bonus::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect objrect = e->getSprite(type_);
    if (is_display_)
        e->draw(objrect, SDL_Rect{x_, y_, w_, h_});
}

void Bonus::try_update(int dt) {
    keep_time_ -= dt;
    if (keep_time_ <= 0)
        is_destroyed_ = true;
    else if (keep_time_ <= 5000) {
        flash_cycle_ -= dt;
        if (flash_cycle_ <= 0) {
            is_display_ = !is_display_;
            flash_cycle_ = 100;
        }
    }
}