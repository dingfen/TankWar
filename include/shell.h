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

    void update(int) override;

    void destroy();
    bool is_destroy();
private:
    double speed_;
    Direction direction_;
    bool is_destroyed_;

    void init();
    bool check_boundary();
};

#endif // _DF_TANKWAR_SHELL_H