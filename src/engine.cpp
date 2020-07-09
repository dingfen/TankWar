#include "engine.h"

Engine::Engine() throw()
    : win_(nullptr), loadsuf_(nullptr), painter_(nullptr), sc_(nullptr) {
    win_ = SDL_CreateWindow("df-tankwar", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        AppConfig::window_rect.w, AppConfig::window_rect.h, SDL_WINDOW_SHOWN);
    if (!win_)
        throw SDLErrorException();
    loadsuf_ = IMG_Load(AppConfig::texture_path().c_str());
    if (!loadsuf_)
        throw SDLErrorException();
    sc_ = SpriteConfig::getInstance();
    painter_ = new Painter(win_, loadsuf_);
}

Engine::~Engine() {
    if (painter_)
        delete painter_;
    if (loadsuf_) {
        SDL_FreeSurface(loadsuf_);
        loadsuf_ = nullptr;
    }
    if (win_) {
        SDL_DestroyWindow(win_);
        win_ = nullptr;
    }
}

void Engine::update() {
    painter_->update();
}

void Engine::drawRect(const SDL_Rect& srcrect, const SDL_Rect& dstrect) {
    painter_->drawRect(srcrect, dstrect);
}

void Engine::writeText(int x, int y, const std::string & text, SDL_Color color) {
    painter_->writeText(x, y, text, color);
}