#include "brick.h"

Brick::Brick(double x, double y)
    : Object(x, y, SpriteType::BRICK_WALL),
    is_destroyed_(false), health_point_(AppConfig::brick_hp) {
    
}

Brick::Brick(SDL_Point p)
    : Object(p, SpriteType::BRICK_WALL),
    is_destroyed_(false), health_point_(AppConfig::brick_hp) {
}

Brick::~Brick() {
    
}

void Brick::boom(int d) {
    health_point_ -= d;
    if (health_point_ <= 0) {
        is_destroyed_ = true;
        health_point_ = 0;
    }
}

bool Brick::is_destroy() {
    return is_destroyed_;
}