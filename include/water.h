/*
 * Water class
 * stands for water in the Game
 */
#ifndef _DF_TANKWAR_WATER_H
#define _DF_TANKWAR_WATER_H

#include "object.h"

class Water : public Object {
public:
    Water(double x, double y);
    Water(SDL_Point);

    ~Water();

    void draw() override;

    void try_update(int) override;
    
    static const int water_flicker = 350;
private:
    int flash_cycle_;   // the water flicker cycle
    int texture_off_;   // when water flicker, it needs change the png
};

#endif // _DF_TANKWAR_WATER_H