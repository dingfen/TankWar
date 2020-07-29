/*
 * Player Class
 * derived from Tank class
 * player controlls it
 */
 
#ifndef _DF_TANKWAR_PLAYER_H
#define _DF_TANKWAR_PLAYER_H

#include "tank.h"
#include "type.h"


class Player : public Tank {
public:
    Player(int, double x, double y, PlayerData);
    Player(int, SDL_Point, PlayerData);
    ~Player();

    void try_update(int) override;

    void do_update() override;

    void addscore();

    // @return whether player's lifes to zero
    bool respawn();

    PlayerData* getdata();
private:
    PlayerData data_;
    bool is_stop_;
};

#endif // _DF_TANKWAR_PLAYER_H