#include "enemy.h"
#include <cstdlib>

void Enemy::init(int kind) {
    srand(time(NULL));
    refire_time_ = rand() % 400 + 1000;
    moving_time_ = rand() % 400 + 1000;
    kind_ = kind;
}

Enemy::Enemy(double x, double y, SpriteType type, int kind)
    : Tank(x, y, type) {
    init(kind);
}

Enemy::Enemy(SDL_Point p, SpriteType type, int kind)
    : Tank(p, type) {
    init(kind);
}

Enemy::~Enemy() {
    
}

void Enemy::try_update(int dt) {
    // random choose a direction
    // keep random time
    srand(time(NULL));
    fire(dt);
    moving_time_ -= dt;
    if (moving_time_ <= 0) {
        direction_ = (Direction)((rand() % 4) * 32);
        moving_time_ = rand() % 400 + 1000;
    }
    Tank::try_update(dt);
}

void Enemy::fire(int dt) {
    srand(time(NULL));
    refire_time_ -= dt;
    if (refire_time_ <= 0) {
        Tank::fire();
        refire_time_ = rand() % 400 + 1000;
    }
}