#include "engine.h"

Engine::Engine()
    : win_(nullptr), loadsuf_(nullptr), painter_(nullptr), sc_(nullptr) {
    try {
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
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
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

void Engine::clear() {
    try {
        painter_->clear();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
}

void Engine::draw(const SDL_Rect& srcrect, const SDL_Rect& dstrect) {
    try {
        painter_->draw(srcrect, dstrect);
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::writeText(SDL_Point point, const std::string & text, 
    const SDL_Color &color, int fontsize, int fontfamily) {
    try {
        painter_->writeText(point, text, color, fontsize, fontfamily);
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::drawRect(const SDL_Rect& srcrect, const SDL_Color& color, bool is_fill) {
    try {
        painter_->drawRect(srcrect, color, is_fill);
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}