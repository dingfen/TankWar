/*
 * Brick class
 * stands for bricks in the Game
 */
#ifndef _DF_TANKWAR_BRICK_H
#define _DF_TANKWAR_BRICK_H

#include "object.h"

class Shell;

class Brick : public Object {
public:
    Brick(double x, double y);
    Brick(SDL_Point);

    ~Brick();

    // void draw() override;

    // void update(int) override;
    
    bool is_destroy() override;
    void boom(Shell *);
private:
    bool is_destroyed_;
    int health_point_;
    
    // 0 all intact
    // 1 up intact
    // 2 right intact
    // 3 down intact
    // 4 left intact
    // 5 up right intact
    // 6 down right intact
    // 7 up left intact
    // 8 down left intact
    int texture_off_;

    // when brick wall is broken
    // x,y,h,w must be changed
    void breakdown(int texture_off);
};

#endif // _DF_TANKWAR_BRICK_H