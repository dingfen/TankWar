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

    void try_update(int) override;

    void do_update() override;

    virtual void fire();

    bool is_destroy() override;
    void destroy();
    bool is_boom() const;
    virtual void boom(int);
    bool is_coming() const;

    void setdirection(Direction);
    Direction getdirection();

    void block();
    void nonblock();
    int getkind() const;
    virtual void setlevel(int l);
    int getlevel();
    std::vector<std::shared_ptr<Shell>>& shells();

    static const int boom_flicker = 70;
    static const int coming_flicker = 100;
protected:
    Direction direction_;
    SDL_Point ori_point_;

    // Tank status
    double speed_;      
    int kind_;          // the Tank A,B,C,D kind
    int level_;         // the Tank level 0 1 2
    int health_point_;

    bool is_destroyed_;
    bool is_boom_;
    bool is_blocked_;
    bool is_coming_;

    int flash_cycle_;   // see Water.h
    int texture_off_;   // see Water.h

    std::vector<std::shared_ptr<Shell>> shells_;

    void init();
};

#endif // _DF_TANKWAR_TANK_H