/*
 * Shell class
 * stands for shells in the Game
 */
#ifndef _DF_TANKWAR_SHELL_H
#define _DF_TANKWAR_SHELL_H

#include "object.h"

class Shell : public Object {
public:
    Shell(double x, double y);
    Shell(SDL_Point);

    ~Shell();

    // void draw() override;

    // void update(int) override;
};

#endif // _DF_TANKWAR_SHELL_H