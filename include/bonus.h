/*
 * Bonus class
 * stands for the bonus appearing after enemy tank killed
 * have several types
 */
#ifndef _DF_TANKWAR_BONUS_H
#define _DF_TANKWAR_BONUS_H

#include "object.h"

class Bonus : public Object {
public:
    Bonus();
    Bonus(double x, double y, SpriteType);
    Bonus(SDL_Point, SpriteType);

    ~Bonus();

    void draw() override;
    void try_update(int) override;
    bool is_destroy() override;
    void destroy();
private:
    bool is_destroyed_;
    bool is_display_;
    int keep_time_;
    int flash_cycle_;
};


#endif // _DF_TANKWAR_BONUS_H