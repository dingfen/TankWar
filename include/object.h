/*
 * Object class
 * which is the base class of all Game Object
 * has some basic properties and API
 */
#ifndef _DF_TANKWAR_OBJECT_H
#define _DF_TANKWAR_OBJECT_H

#include "engine.h"
#include "appconfig.h"


class Object {
public:
    Object(double x, double y, SpriteType type);
    Object(SDL_Point, SpriteType);

    virtual ~Object();

    // draw the object on the screen
    virtual void draw();
    // try update 
    // first aggressively compute the new position 
    virtual void try_update(int);
    // the real update
    // after collision detect, determine if update or roll back 
    virtual void do_update();
    // whether thing has been destroyed
    virtual bool is_destroy();

    double getX() const {return x_;};
    double getY() const {return y_;};
    double getW() const {return w_;};
    double getH() const {return h_;};
    SDL_Rect getRect() const { return SDL_Rect{x_, y_, w_, h_};};
    
    // check if object out of boundary
    static bool checkX(const Object *obj) {
        if (obj->getX() < 0 || obj->getX() > AppConfig::map_rect.w - obj->getW())
            return false;
        else 
            return true;
    }

    static bool checkY(const Object *obj) {
        if (obj->getY() < 0 || obj->getY() > AppConfig::map_rect.h - obj->getH())
            return false;
        else 
            return true;
    }

    static bool check_boundary(const Object* obj) {
        if (!checkX(obj) || !checkY(obj))
            return false;
        else 
            return true;
    }
protected:
    double x_;
    double y_;
    double w_;
    double h_;
    // indicate the object type
    SpriteType type_;
};

#endif // _DF_TANKWAR_OBJECT_H