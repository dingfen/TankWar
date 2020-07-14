/*
 * Tank class
 * stands for tanks in the Game
 */
#ifndef _DF_TANKWAR_TANK_H
#define _DF_TANKWAR_TANK_H

#include "object.h"
#include "shell.h"

class Tank : public Object {
public:
    Tank(double x, double y, SpriteType);
    Tank(SDL_Point, SpriteType);

    virtual ~Tank();

    void draw() override;

    void update(int) override;

    void fire();

    void setdirection(Direction);
    Direction getdirection();
private:
    Direction direction_;
    double speed_;
    bool is_stop_;
    int shells_left_;
    std::vector<Shell> shells;

    void init();
};

#endif // _DF_TANKWAR_TANK_H