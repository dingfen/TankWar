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

void Painter::drawRect(const SDL_Rect& srcrect, const SDL_Rect& dstrect) {
    SDL_RenderCopy(render_, text_, &srcrect, &dstrect);
}

void Painter::writeText(int x, int y,
    const std::string & text, const SDL_Color& color) {
    SDL_Surface *suf = TTF_RenderText_Solid(font_, text.c_str(), color);
    text_ = SDL_CreateTextureFromSurface(render_, suf);
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = suf->w;
    rect.h = suf->h;
    SDL_RenderCopy(render_, text_, NULL, &rect);
}