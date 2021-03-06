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
    Player(int, double x, double y);
    Player(int, SDL_Point);
    ~Player();

    void try_update(int) override;

    void do_update() override;

    void addscore();

    // @return whether player's lifes to zero
    bool respawn();

    void boom(int) override;

    void settanklevel(int) override;
    void setshellevel(int) override;
    PlayerData* getdata();
    void cleandata();
private:
    PlayerData *data_;
    bool is_stop_;

    void init(int);
};

#endif // _DF_TANKWAR_PLAYER_H