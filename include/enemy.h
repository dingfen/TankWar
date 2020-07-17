/*
 * Enemy Class
 * describe the enemy tank behaviour and respawn
 */
#ifndef _DF_TANKWAR_ENEMY_H
#define _DF_TANKWAR_ENEMY_H

#include "tank.h"

class Enemy : public Tank {
public:
    Enemy(double x, double y, SpriteType);
    Enemy(SDL_Point, SpriteType);
    ~Enemy();

    // void draw() override;

    // void try_update(int) override;

    // void do_update() override;

    // virtual void fire();
private:
    
};

#endif // _DF_TANKWAR_ENEMY_H