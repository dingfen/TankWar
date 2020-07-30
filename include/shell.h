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
    int damage();
    Direction getdirection();

    static const int shell_flicker = 50;
private:
    Direction direction_;
    SDL_Point ori_point_;
    double speed_;
    int damage_;
    bool is_destroyed_;
    bool is_boom_;

    int flash_cycle_;   // see Water.h
    int texture_off_;   // see Water.h

    void init();
};

#endif // _DF_TANKWAR_SHELL_H