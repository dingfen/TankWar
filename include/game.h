/*
 * Game class
 * in this class, everything is being renderer
 * main playground
 */

#ifndef _DF_TANKWAR_GAME_H
#define _DF_TANKWAR_GAME_H

#include "appstate.h"
#include "object.h"
#include "bush.h"
#include "player.h"
#include "enemy.h"
#include "eagle.h"
#include <iostream>

using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

class Game : public AppState {
public:
    // print Game playground on the screen
    void draw() override;
    // update what is new
    void update(int) override;
    // event process
    void event(SDL_Event*) override;
    // judge if stage is finished
    bool finish() override;
    // jump to next state
    void nextstate(unique_ptr<AppState>&) override;
    
    Game(int stage, const PlayerData *p1, const PlayerData *p2=nullptr);
    ~Game();
private:
    // 0 game playing 1 game exit by escape 
    // 2 game lose  3 game win 4 game skip
    int is_finished_;
    // game level
    int stage_;
    // game map without bush
    vector<vector<shared_ptr<Object>>> map_;
    vector<shared_ptr<Bush>> bush_;
    // prepare time at the beginning
    int prepare_time_;
    // prepare time when game over
    int over_time_;
    // left enemy number
    int enemy_num_;
    int enemy_on_map_;
    // players
    unique_ptr<Player> p1;
    unique_ptr<Player> p2;
    bool p1_over_;
    bool p2_over_;
    bool hq_destroyed_;
    // Tank t_;
    vector<shared_ptr<Enemy>> enemy_tanks_;

    //miscellaneous
    double game_over_y_pos_;

    void init(const PlayerData *p1, const PlayerData *p2);
    void loadmap();

    // generate enemy tanks
    shared_ptr<Enemy> generatenemy();

    void drawmap();
    void try_update_map(int);
    void do_update_map();
    void drawstatus();
    // void try_update_status(int);
    // void do_update_status();
    void drawbush();    // bush must be last one drawn
    void drawtank();
    void try_update_tank(int);
    void do_update_tank();

    // the top collision detect function
    void collision_detect();
    // collision with player and map
    bool tank_map_collision(const Tank *);
    // collision with tanks
    bool tank_tank_collision(const Tank *,const Tank *);

    // the top booming detect function
    void boom_detect();
    // tank's shell boom the map
    void shell_map_boom(Tank *);
    // tank's shell boom the tank
    void shell_tank_boom(Tank *, Tank *);
};

#endif // _DF_TANKWAR_GAME_H