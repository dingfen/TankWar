/*
 * Object class
 * which is the base class of all Game Object
 * has some basic properties and API
 */
#ifndef _DF_TANKWAR_OBJECT_H
#define _DF_TANKWAR_OBJECT_H

#include "engine.h"

enum class Direction {
    UP = 0, RIGHT = 32, DOWN = 64, LEFT = 96
};

class Object {
public:
    Object(double x, double y, SpriteType type);
    Object(SDL_Point, SpriteType);

    virtual ~Object();

    // draw the object on the screen
    virtual void draw();

    // update
    virtual void update(int);
protected:
    double x_;
    double y_;
    // indicate the object type
    SpriteType type_;

    inline bool check_boundary();
};

#endif // _DF_TANKWAR_OBJECT_H