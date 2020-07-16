/*
 * Game class
 * in this class, everything is being renderer
 * main playground
 */

#ifndef _DF_TANKWAR_GAME_H
#define _DF_TANKWAR_GAME_H

#include "appstate.h"
#include "object.h"
#include "player.h"
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
    
    Game(int stage);
    ~Game();
private:
    bool is_finished_;
    // game level
    int stage_;
    // game map
    vector<vector<shared_ptr<Object>>> map_;
    // prepare time at the beginning
    int prepare_time_;
    // left enemy number
    int enemy_num_;
    // players
    unique_ptr<Player> p1;
    unique_ptr<Player> p2;
    // Tank t_;

    void init();
    void loadmap();

    void drawmap();
    void drawstatus();

    // the top collision detect function
    void collision_detect();
    // collision with player and map
    bool player_map_collision(const unique_ptr<Player>&);
    
};

#endif // _DF_TANKWAR_GAME_H