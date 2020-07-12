#include "app.h"
#include "menu.h"
#include "store.h"
#include "engine.h"

App::App()
    : is_running_(false) {}

App::~App() {
    is_running_ = false;
}

void App::init() throw() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw SDLErrorException();
    }
    int imgflags = IMG_INIT_PNG;
    if (!(IMG_Init(imgflags) & imgflags)) {
        throw SDLErrorException();
    }
    if (TTF_Init() == -1) {
        throw SDLErrorException();
    }
}

void App::run() {
    try {
        init();
        // load Menu
        app_state_ = unique_ptr<AppState>(new Menu());
        app_state_->draw();
        app_state_->update(0);

        is_running_ = true;
        Uint32 time1, time2, delay = 15, duration;
        time1 = SDL_GetTicks();
        while(is_running_) {
            // processing one loop duration
            time2 = SDL_GetTicks();
            duration = time2 - time1;
            time1 = time2;

            this->event();
            if (app_state_->finish()) {
                app_state_->nextstate(app_state_);
            } else {
                app_state_->draw();
                app_state_->update(duration);
            }
            if (!app_state_) break;
            
            // avoid testing too fast
            // if run too slow, should increase duration
            SDL_Delay(delay);

        }
    } catch(const std::exception &e) {
        cerr << e.what() << endl;
        SDL_ClearError();
    }
}

void App::event() {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            is_running_ = false;
        }

        app_state_->event(&e);
    }
}