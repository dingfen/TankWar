#include "enemy.h"
#include <cstdlib>

void Enemy::init() {
    srand(time(NULL));
    refire_time_ = rand() % 400;
    moving_time_ = rand() % 400 + 1000;
}

Enemy::Enemy(double x, double y, SpriteType type)
    : Tank(x, y, type) {
}

Enemy::Enemy(SDL_Point p, SpriteType type)
    : Tank(p, type) {
}

Enemy::~Enemy() {
    
}

void Enemy::try_update(int dt) {
    // random choose a direction
    // keep random time
    srand(time(NULL));
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
        refire_time_ = rand() % 400;
    }
}