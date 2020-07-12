/*
 * Game class
 * in this class, everything is being renderer
 * main playground
 */

#ifndef _DF_TANKWAR_GAME_H
#define _DF_TANKWAR_GAME_H

#include "appstate.h"
#include "object.h"
#include <iostream>

using std::vector;
using std::unique_ptr;

class Game : public AppState {
public:
    // print Game playground on the screen
    void draw() override;
    // update what is new
    void update() override;
    // event process
    void event(SDL_Event*) override;
    // judge if stage is finished
    bool finish() override;
    // jump to next state
    void nextstate(std::unique_ptr<AppState>&) override;
    
    Game(int stage);
    ~Game();
private:
    bool is_finished_;
    // game level
    int stage_;
    // game map
    vector<vector<unique_ptr<Object>>> map_;
    // 

    void loadmap();
};

#endif // _DF_TANKWAR_GAME_H