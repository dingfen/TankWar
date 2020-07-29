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

    // count time to fire
    void fire(int);
private:
    int refire_time_;
    int moving_time_;
    void init(int);
};

#endif // _DF_TANKWAR_ENEMY_H