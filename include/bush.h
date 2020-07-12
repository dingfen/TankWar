/*
 * Bush class
 * stands for bush in the Game
 */
#ifndef _DF_TANKWAR_BUSH_H
#define _DF_TANKWAR_BUSH_H

#include "object.h"

class Bush : public Object {
public:
    Bush(double x, double y);
    Bush(SDL_Point);

    ~Bush();

    // void draw() override;

    // void update(int) override;
};

#endif // _DF_TANKWAR_BUSH_H