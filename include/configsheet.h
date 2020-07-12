/*
 * ConfigSheet class
 * show the config and help info
 * derived from AppState
 */ 
#ifndef _DF_TANKWAR_CONFIGSHEET_H
#define _DF_TANKWAR_CONFIGSHEET_H

#include "appstate.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class ConfigSheet : public AppState {
public:
    void draw() override;

    void update(int) override;

    void event(SDL_Event *) override;

    bool finish() override;

    void nextstate(std::unique_ptr<AppState>&) override;

    ConfigSheet();
    ~ConfigSheet() {};
private:
    bool is_finished_;
    vector<string> lines_;    
};

#endif // _DF_TANKWAR_CONFIGSHEET_H