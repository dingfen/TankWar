#include "engine.h"

Engine::Engine() throw()
    : win_(nullptr), loadsuf_(nullptr), render_(nullptr), 
    text_(nullptr), sc_(nullptr) {
    win_ = SDL_CreateWindow("df-tankwar", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        AppConfig::window_rect.w, AppConfig::window_rect.h, SDL_WINDOW_SHOWN);
    if (!win_)
        throw SDLErrorException();
    loadsuf_ = IMG_Load(AppConfig::texture_path().c_str());
    render_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
    if (!render_)
        throw SDLErrorException();
    text_ = SDL_CreateTextureFromSurface(render_, loadsuf_);
    if (!text_)
        throw SDLErrorException();
    sc_ = SpriteConfig::getInstance();
}

Engine::~Engine() {
    if (text_) {
        SDL_DestroyTexture(text_);
        text_ = nullptr;
    }
    if (render_) {
        SDL_DestroyRenderer(render_);
        render_ = nullptr;
    }
    if (loadsuf_) {
        SDL_FreeSurface(loadsuf_);
        loadsuf_ = nullptr;
    }
    if (win_) {
        SDL_DestroyWindow(win_);
        win_ = nullptr;
    }
}