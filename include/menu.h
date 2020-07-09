/*
 * Menu class
 * at the beginning of the App
 * show this Menu, derived from AppState
 */ 

#ifndef _DF_TANKWAR_MENU_H
#define _DF_TANKWAR_MENU_H

#include "appstate.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Menu : public AppState {
public:
    // print Menu list on the screen
    void draw() override;
    // update what is new
    void update() override;

    Menu();
    ~Menu();
private:
    vector<string> items;
    
};


#endif // _DF_TANKWAR_MENU_H