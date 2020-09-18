/*
 * Enemy Class
 * describe the enemy tank behaviour and respawn
 */
#ifndef _DF_TANKWAR_ENEMY_H
#define _DF_TANKWAR_ENEMY_H

#include "tank.h"

class Enemy : public Tank {
public:
    Enemy(double x, double y, SpriteType, int);
    Enemy(SDL_Point, SpriteType, int);
    ~Enemy();

    // void draw() override;

    void try_update(int) override;

    // void do_update() override;

    void boom(int d) override;

    // count time to fire
    void fire(int);
    void setkind(int);
    void setarget(SDL_Point p1, SDL_Point p2, SDL_Point pe);

    static const int refire = 800;
private:
    int refire_time_;       // enemy tank fire at constant time
    int moving_time_;
    int sum_hp_;
    SDL_Point target;

    void init(int);
    Direction route();
};

#endif // _DF_TANKWAR_ENEMY_H