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
    health_point_ -= d;
    if (health_point_ <= 0) {
        is_destroyed_ = true;
        health_point_ = 0;
    }
}

bool Stone::is_destroy() {
    return is_destroyed_;
}