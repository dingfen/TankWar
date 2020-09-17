#include "enemy.h"
#include <cstdlib>

void Enemy::init(int kind) {
    srand(time(NULL));
    refire_time_ = rand() % 400 + 1000;
    moving_time_ = rand() % 400 + 1000;
    settanklevel(0);
    setshellevel(0);
    sum_hp_ = health_point_;
    setkind(kind);
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

void Enemy::setkind(int k) {
    kind_ = k;
    if (kind_ > 0) {
        health_point_ = sum_hp_ * (kind_+1);
    }
}

void Enemy::boom(int d) {
    health_point_ -= d;
    if (kind_ != -1)
        kind_ = (health_point_ -1) / sum_hp_;
    if (health_point_ <= 0) {
        is_boom_ = true;
        health_point_ = 0;
    }
}
