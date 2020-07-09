#include "painter.h"

Painter::Painter(SDL_Window *win, SDL_Surface *suf) throw(){
    render_ = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!render_)
        throw SDLErrorException();
    text_ = SDL_CreateTextureFromSurface(render_, suf);
    if (!text_)
        throw SDLErrorException();
    font_ = TTF_OpenFont(AppConfig::font_path().c_str(), 14);
    if (!font_)
        throw TTFErrorException();
    ttf_text_ = nullptr;
}


Painter::~Painter() {
    if (text_) {
        SDL_DestroyTexture(text_);
        text_ = nullptr;
    }
    if (render_) {
        SDL_DestroyRenderer(render_);
        render_ = nullptr;
    }
}

void Painter::update() {
    if (render_)
        SDL_RenderPresent(render_);
}

void Painter::clear() throw() {
    if (SDL_SetRenderDrawColor(render_, 0, 0, 0, 255) == -1)
        throw SDLErrorException();
    if (SDL_RenderClear(render_) == -1)
        throw SDLErrorException();
}

void Painter::drawRect(const SDL_Rect& srcrect, const SDL_Rect& dstrect) throw() {
    if (SDL_RenderCopy(render_, text_, &srcrect, &dstrect) == -1)
        throw SDLErrorException();
}

void Painter::writeText(int x, int y,
    const std::string & text, const SDL_Color& color) throw() {
    SDL_Surface *suf = TTF_RenderText_Solid(font_, text.c_str(), color);
    if (!suf)
        throw TTFErrorException();
    ttf_text_ = SDL_CreateTextureFromSurface(render_, suf);
    if (!ttf_text_)
        throw SDLErrorException();
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = suf->w;
    rect.h = suf->h;
    if (SDL_RenderCopy(render_, ttf_text_, NULL, &rect) == -1)
        throw SDLErrorException();
}