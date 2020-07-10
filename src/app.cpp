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
        app_state_->update();

        is_running_ = true;
        while(is_running_) {
            this->event();
            if (app_state_->finish()) {
                app_state_.reset(new Store());
            } else {
                app_state_->draw();
                app_state_->update();
            }
            // avoid testing too fast
            SDL_Delay(15);
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