/*
 * Eagle class
 * stands for the headquater of ours.
 * if destroyed, game over
 */
#ifndef _DF_TANKWAR_EAGLE_H
#define _DF_TANKWAR_EAGLE_H

#include "object.h"

class Eagle : public Object {
public:
    Eagle();
    Eagle(double x, double y);
    Eagle(SDL_Point);

    ~Eagle();

    void draw() override;

    // void update(int) override;
    bool is_destroy() override;
    void boom(int);
private:
    bool is_destroyed_;
    int health_point_;
};


#endif // _DF_TANKWAR_EAGLE_H