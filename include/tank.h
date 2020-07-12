/*
 * Tank class
 * stands for tanks in the Game
 */
#ifndef _DF_TANKWAR_TANK_H
#define _DF_TANKWAR_TANK_H

#include "object.h"

class Tank : public Object {
public:
    Tank(double x, double y);
    Tank(SDL_Point);

    ~Tank();

    // void draw() override;

    // void update(int) override;
};

#endif // _DF_TANKWAR_TANK_H