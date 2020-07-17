#include "brick.h"

Brick::Brick(double x, double y)
    : Object(x, y, SpriteType::BRICK_WALL),
    is_destroyed_(false), health_point_(10) {
    
}

Brick::Brick(SDL_Point p)
    : Object(p, SpriteType::BRICK_WALL),
    is_destroyed_(false), health_point_(10) {
}

Brick::~Brick() {
    
}

void Brick::boom(int d) {
    if (health_point_ <= d)
        is_destroyed_ = true;
}