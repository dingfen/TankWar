/*
 * Store class
 * when u won a level 
 * u can use money to buy something
 * derived from AppState
 */
#ifndef _DF_TANKWAR_STORE_H
#define _DF_TANKWAR_STORE_H

#include "appstate.h"
#include "player.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Store : public AppState {
public:
    // print Store goods on the screen
    void draw() override;
    // update what is new
    void update(int) override;
    // event process
    void event(SDL_Event*) override;
    // judge if stage is finished
    bool finish() override;
    // jump to next state
    void nextstate(std::unique_ptr<AppState>&) override;
    Store(int);
    ~Store();

    static const int line_spacing_ = 32;
private:
    vector<std::pair<string, int>> goods_;
    int is_finished_;
    int stage_;

    const PlayerData *pd1;
    const PlayerData *pd2;
    int player_nums;

    int cursor_pos_;
    int p1_offset_;
    int p2_offset_;

    void show_money(int i, SDL_Rect icon);
    void show_goods(SDL_Rect);
    void init_goods();
    void buy(int);
};

#endif // _DF_TANKWAR_STORE_H