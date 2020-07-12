/*
 * Ice class
 * stands for ice in the Game
 */
#ifndef _DF_TANKWAR_ICE_H
#define _DF_TANKWAR_ICE_H

#include "object.h"

class Ice : public Object {
public:
    Ice(double x, double y);
    Ice(SDL_Point);

    ~Ice();

    // void draw() override;

    // void update(int) override;
};

#endif // _DF_TANKWAR_ICE_H