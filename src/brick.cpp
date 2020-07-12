#include "brick.h"

Brick::Brick(double x, double y)
    : Object(x, y, SpriteType::BRICK_WALL) {

}

Brick::Brick(SDL_Point p)
    : Object(p, SpriteType::BRICK_WALL) {

}

Brick::~Brick() {
    
}