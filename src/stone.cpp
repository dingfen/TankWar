#include "stone.h"
#include "shell.h"

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

void Stone::boom(Shell *s) {
    if (s->getlevel() < 1)
        return ;
    health_point_ -= s->damage();
    if (health_point_ <= 0) {
        is_destroyed_ = true;
        health_point_ = 0;
    }
}

bool Stone::is_destroy() {
    return is_destroyed_;
}