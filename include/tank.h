/*
 * Tank class
 * stands for tanks in the Game
 */
#ifndef _DF_TANKWAR_TANK_H
#define _DF_TANKWAR_TANK_H

#include "object.h"
#include "shell.h"
#include <memory>

class Tank : public Object {
public:
    Tank(double x, double y, SpriteType);
    Tank(SDL_Point, SpriteType);

    virtual ~Tank();

    void draw() override;

    void update(int) override;

    virtual void fire();

    void setdirection(Direction);
    Direction getdirection();
    bool is_destroy();
protected:
    Direction direction_;
    double speed_;
    
    bool is_destroyed_;
    bool is_stop_;

    std::vector<std::shared_ptr<Shell>> shells;

    void init();
};

#endif // _DF_TANKWAR_TANK_H