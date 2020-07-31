/*
 * Shell class
 * stands for shells in the Game
 */
#ifndef _DF_TANKWAR_SHELL_H
#define _DF_TANKWAR_SHELL_H

#include "object.h"

class Shell : public Object {
public:
    Shell(double x, double y, Direction);
    Shell(SDL_Point, Direction);

    ~Shell();

    void draw() override;

    void try_update(int) override;

    void do_update() override;

    bool is_destroy() override;
    void destroy();
    bool is_boom();
    void boom();

    int getlevel();
    void setlevel(int);

    int damage();
    void setdamage(int);

    void setspeed(int);
    Direction getdirection();

    static const int shell_flicker = 50;
private:
    Direction direction_;
    SDL_Point ori_point_;

    // shell properties 
    // level 0 can destroy half brick
    // level 1 can destroy whole brick and stone
    // level 2 can destroy whole stone speed up to 150%
    double speed_;
    int damage_;
    int level_;

    bool is_destroyed_;
    bool is_boom_;

    int flash_cycle_;   // see Water.h
    int texture_off_;   // see Water.h

    void init();
};

#endif // _DF_TANKWAR_SHELL_H