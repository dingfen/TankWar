/*
 * DebugScene class
 * won't be compiled if DEBUG not defined
 * designed for Debug
 */ 

// #ifdef DEBUG

#ifndef _DF_TANKWAR_DEBUG_H
#define _DF_TANKWAR_DEBUG_H

#include "appstate.h"
#include "appconfig.h"

class DebugScene : public AppState {
public:
    void draw() override;
    void update(int) override;
    void event(SDL_Event *) override;
    bool finish() override;
    void nextstate(std::unique_ptr<AppState> &) override;

    DebugScene();
    ~DebugScene();

private:
    int prepare_time_;
    bool is_finished_;
};


#endif // _DF_TANKWAR_DEBUG_H

// #endif // DEBUG