/*
 * Stone class
 * stands for Stone in the Game
 */
#ifndef _DF_TANKWAR_STONE_H
#define _DF_TANKWAR_STONE_H

#include "object.h"

class Stone : public Object {
public:
    Stone(double x, double y);
    Stone(SDL_Point);

    ~Stone();

    // void draw() override;

    // void update(int) override;
};

#endif // _DF_TANKWAR_STONE_H