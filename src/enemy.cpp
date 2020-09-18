#include "enemy.h"
#include <cstdlib>

void Enemy::init(int kind) {
    srand(time(NULL));
    refire_time_ = refire;
    moving_time_ = rand() % 400 + 1000;
    settanklevel(0);
    setshellevel(0);
    sum_hp_ = health_point_;
    setkind(kind);
    target.x = 12*16;
    target.y = 24*16;
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

Direction Enemy::route() {
    srand(time(NULL));
    int p = rand() % 100;
    bool t, lr, ud;
    if (type_ == SpriteType::TANK_A)
        t = p < 80;
    else
        t = p < 50;
    if (t) {
        lr = (target.x - x_) > 0;
        ud = (target.y - y_) > 0;
        if (lr) {
            if (rand() % 2)
                return Direction::RIGHT;
            else {
                if (ud) return Direction::DOWN;
                else return Direction::UP;
            }
        } else {
            if (rand() % 2)
                return Direction::LEFT;
            else {
                if (ud) return Direction::DOWN;
                else return Direction::UP;
            }
        }
    } else {
        return (Direction)((rand() % 4) * 32);
    }
}

void Enemy::try_update(int dt) {
    // random choose a direction
    // keep random time
    srand(time(NULL));
    fire(dt);
    moving_time_ -= dt;
    if (moving_time_ <= 0) {
        direction_ = route();
        moving_time_ = rand() % 400 + 1000;
    }
    Tank::try_update(dt);
}

void Enemy::fire(int dt) {
    srand(time(NULL));
    refire_time_ -= dt;
    if (refire_time_ <= 0) {
        Tank::fire();
        refire_time_ = refire;
    }
}

void Enemy::setkind(int k) {
    kind_ = k;
    if (kind_ > 0) {
        health_point_ = sum_hp_ * (kind_+1);
    }
}

void Enemy::setarget(SDL_Point p1, SDL_Point p2, SDL_Point pe) {
    if (type_ == SpriteType::TANK_B || type_ == SpriteType::TANK_C) {
        target = pe;
        return;
    }
    double d1, d2, d3;
    if (p2.x == -1 || p2.y == -1)
        d2 = INT32_MAX;
    else 
        d2 = abs(x_-p2.x) + abs(y_-p2.y);   
    d1 = abs(x_-p1.x) + abs(y_-p1.y);
    d3 = abs(x_-pe.x) + abs(y_-pe.y);
    if (d1 > d2) {
        if (d2 > d3)
            target = pe;
        else 
            target = p2;
    } else {
        if (d1 > d3)
            target = pe;
        else
            target = p1;
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
