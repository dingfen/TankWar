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

    double getX() {return x_;};
    double getY() {return y_;};
    double getW() {return w_;};
    double getH() {return h_;};
protected:
    double x_;
    double y_;
    double w_;
    double h_;
    // indicate the object type
    SpriteType type_;
};

#endif // _DF_TANKWAR_OBJECT_H