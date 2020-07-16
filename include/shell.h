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

    void destroy();
    bool is_destroy();
    void boom();
private:
    SDL_Point ori_point_;
    double speed_;
    Direction direction_;
    bool is_destroyed_;
    bool is_boom_;

    void init();
};

#endif // _DF_TANKWAR_SHELL_H