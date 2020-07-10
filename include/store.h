/*
 * Store class
 * when u won a level 
 * u can use money to buy something
 * derived from AppState
 */
#ifndef _DF_TANKWAR_STORE_H
#define _DF_TANKWAR_STORE_H

#include "appstate.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Store : public AppState {
public:
    // print Store goods on the screen
    void draw() override;
    // update what is new
    void update() override;
    // event process
    void event(SDL_Event*) override;
    // judge if stage is finished
    bool finish() override;

    Store();
    ~Store();
private:
    vector<string> goods_;
    bool is_finished_;
};

#endif // _DF_TANKWAR_STORE_H