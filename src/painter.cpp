#include "painter.h"

Painter::Painter(SDL_Window *win, SDL_Surface *suf) {
    render_ = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!render_)
        throw SDLErrorException();
    text_ = SDL_CreateTextureFromSurface(render_, suf);
    if (!text_)
        throw SDLErrorException();
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

void Painter::drawRect(const SDL_Rect& srcrect, const SDL_Rect& dstrect) {
    SDL_RenderCopy(render_, text_, &srcrect, &dstrect);
    SDL_RenderPresent(render_);
}