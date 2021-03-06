#include "eagle.h"

Eagle::Eagle()
    : Object(12 * AppConfig::tile_w, 24 * AppConfig::tile_h, SpriteType::EAGLE),
    is_destroyed_(false), health_point_(AppConfig::eagle_hp) {
    w_ = 32;
    h_ = 32;
}

Eagle::Eagle(double x, double y)
    : Object(x, y, SpriteType::EAGLE),
    is_destroyed_(false), health_point_(AppConfig::eagle_hp) {
    w_ = 32;
    h_ = 32;
}

Eagle::Eagle(SDL_Point p)
    : Object(p, SpriteType::EAGLE),
    is_destroyed_(false), health_point_(AppConfig::eagle_hp) {
    w_ = 32;
    h_ = 32;
}

Eagle::~Eagle() {
    
}

void Eagle::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect obj = e->getSprite(type_, (int)is_destroyed_);
    e->draw(obj, SDL_Rect{x_, y_, w_, h_});
}

void Eagle::boom(int d) {
    health_point_ -= d;
    if (health_point_ <= 0) {
        is_destroyed_ = true;
        health_point_ = 0;
    }
}

bool Eagle::is_destroy() {
    return is_destroyed_;
}