/*
 * App class
 * app run/pause/save operations
 */
#ifndef _DF_TANKWAR_APP_H
#define _DF_TANKWAR_APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "appstate.h"

using std::cerr;
using std::endl;
using std::unique_ptr;

class App {
public:
    static App* getInstance() {
        static App app;
        return &app;
    }

    // App start run
    void run();

    // App process key/mouse event
    void event();
private:
    App();
    App(App const&);
    App& operator=(App const&);
    ~App();

    void init() throw();

    bool is_running_;    // whether the game is running
    unique_ptr<AppState> app_state_;    // a ptr to the state
};

#endif // _DF_TANKWAR_APP_H