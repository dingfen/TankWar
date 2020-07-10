#include "painter.h"

Painter::Painter(SDL_Window *win, SDL_Surface *suf) throw(){
    render_ = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!render_)
        throw SDLErrorException();
    text_ = SDL_CreateTextureFromSurface(render_, suf);
    if (!text_)
        throw SDLErrorException();
    font_size_ = 14;
    font_ = TTF_OpenFont(AppConfig::font_path().c_str(), font_size_);
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
    if (font_) {
        TTF_CloseFont(font_);
        font_ = nullptr;
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

void Painter::draw(const SDL_Rect& srcrect, const SDL_Rect& dstrect) throw() {
    if (SDL_RenderCopy(render_, text_, &srcrect, &dstrect) == -1)
        throw SDLErrorException();
}

void Painter::drawRect(const SDL_Rect& srcrect, 
    SDL_Color color, bool is_fill) throw() {
    if (SDL_SetRenderDrawColor(render_, color.r, color.g, color.b, color.a) == -1)
        throw SDLErrorException();

    if (is_fill) {
        if (SDL_RenderFillRect(render_, &srcrect) == -1)
            throw SDLErrorException();
    } else {
        if (SDL_RenderDrawRect(render_, &srcrect) == -1)
            throw SDLErrorException();
    }
}

void Painter::writeText(SDL_Point point, 
    const std::string & text, const SDL_Color& color, int fontsize) throw() {
    // exsiting TTF fontsize != required fontsize
    if (font_size_ != fontsize) {
        if (font_) {
            TTF_CloseFont(font_);
            font_ = nullptr;
        }
        font_ = TTF_OpenFont(AppConfig::font_path().c_str(), fontsize);
    }
    SDL_Surface *suf = TTF_RenderText_Solid(font_, text.c_str(), color);
    if (!suf)
        throw TTFErrorException();
    ttf_text_ = SDL_CreateTextureFromSurface(render_, suf);
    if (!ttf_text_)
        throw SDLErrorException();
    
    SDL_Rect rect;
    rect.w = suf->w;
    rect.h = suf->h;
    // make it easy to be put in the middle
    if (point.x < 0)
        rect.x = (AppConfig::window_rect.w - suf->w) / 2;
    else rect.x = point.x;
    if (point.y < 0)
        rect.y = (AppConfig::window_rect.h - suf->h) / 2;
    else rect.y = point.y;
    
    if (SDL_RenderCopy(render_, ttf_text_, NULL, &rect) == -1)
        throw SDLErrorException();
}

// void Painter::drawLine(const SDL_Point& start, const SDL_Point& end,
//     SDL_Color color) throw() {
//     SDL_SetRenderDrawColor();
//     SDL_RenderDrawLine()
// }