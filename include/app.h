/*
 * App class
 * app run/pause/save operations
 */
#ifndef _DF_TANKWAR_APP_H
#define _DF_TANKWAR_APP_H

#include "appstate.h"

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