#include "stone.h"

Stone::Stone(double x, double y)
    : Object(x, y, SpriteType::STONE_WALL) {

}

Stone::Stone(SDL_Point p)
    : Object(p, SpriteType::STONE_WALL) {

}

Stone::~Stone() {
    
}