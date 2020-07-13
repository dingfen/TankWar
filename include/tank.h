/*
 * Tank class
 * stands for tanks in the Game
 */
#ifndef _DF_TANKWAR_TANK_H
#define _DF_TANKWAR_TANK_H

#include "object.h"

enum class Direction {
    UP = 0, RIGHT = 32, DOWN = 64, LEFT = 96
};


class Tank : public Object {
public:
    Tank(double x, double y, SpriteType);
    Tank(SDL_Point, SpriteType);

    virtual ~Tank();

    void draw() override;

    void update(int) override;

    void setdirection(Direction);
    Direction getdirection();
private:
    Direction direction_;
    double speed_;
    bool is_stop_;

    void init();
};

#endif // _DF_TANKWAR_TANK_H