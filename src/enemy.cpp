#include "enemy.h"


Enemy::Enemy(double x, double y, SpriteType type)
    : Tank(x, y, type) {
}

Enemy::Enemy(SDL_Point p, SpriteType type)
    : Tank(p, type) {
}

Enemy::~Enemy() {
    
}