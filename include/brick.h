/*
 * Brick class
 * stands for bricks in the Game
 */
#ifndef _DF_TANKWAR_BRICK_H
#define _DF_TANKWAR_BRICK_H

#include "object.h"

class Brick : public Object {
public:
    Brick(double x, double y);
    Brick(SDL_Point);

    ~Brick();

    // void draw() override;

    // void update(int) override;
private:
    bool is_destroyed_;
};

#endif // _DF_TANKWAR_BRICK_H