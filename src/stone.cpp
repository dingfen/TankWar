#include "stone.h"

Stone::Stone(double x, double y)
    : Object(x, y, SpriteType::STONE_WALL),
    is_destroyed_(false), health_point_(AppConfig::stone_hp) {
}

Stone::Stone(SDL_Point p)
    : Object(p, SpriteType::STONE_WALL),
    is_destroyed_(false), health_point_(AppConfig::stone_hp) {
}

Stone::~Stone() {
    
}

void Stone::boom(int d) {
    if (health_point_ <= d)
        is_destroyed_ = true;
}

bool Stone::is_destroy() {
    return is_destroyed_;
}