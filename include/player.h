/*
 * Player Class
 * derived from Tank class
 * player controlls it
 */
 
#ifndef _DF_TANKWAR_PLAYER_H
#define _DF_TANKWAR_PLAYER_H

#include "tank.h"

class Player : public Tank {
public:
    Player(int, double x, double y);
    Player(int, SDL_Point);
    ~Player();

    void try_update(int) override;

    void do_update() override;
private:
    int player_id_;
    int score_;
    bool is_stop_;

    void init();
};

#endif // _DF_TANKWAR_PLAYER_H