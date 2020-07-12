/*
 * Water class
 * stands for water in the Game
 */
#ifndef _DF_TANKWAR_WATER_H
#define _DF_TANKWAR_WATER_H

#include "object.h"

class Water : public Object {
public:
    Water(double x, double y);
    Water(SDL_Point);

    ~Water();

    // void draw() override;

    // void update(int) override;
};

#endif // _DF_TANKWAR_WATER_H