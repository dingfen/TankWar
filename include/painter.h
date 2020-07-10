/*
 * Painter class
 * wrapper of the specific drawing details
 * make drawing easy
 */ 
#ifndef _DF_TANKWAR_PAINTER_H
#define _DF_TANKWAR_PAINTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "exception.h"
#include "appconfig.h"
#include "spriteconfig.h"

class Painter {
public:
    Painter(SDL_Window *, SDL_Surface *) throw();
    ~Painter();

    // update the screen with rendering performed
    void update();

    // clear the screen
    void clear() throw();
    // draw a object on render
    // src position in texture png
    // dst position on window
    void draw(const SDL_Rect& srcrect, const SDL_Rect& dstrect) throw();

    // write text using color
    void writeText(SDL_Point, const std::string&, 
        const SDL_Color&, int, int) throw();

    // draw a Rect
    // whether fill or draw depends on the is_fill
    void drawRect(const SDL_Rect& rect, SDL_Color color, bool is_fill) throw();
private:
    SDL_Renderer *render_;
    SDL_Texture *text_;
    SDL_Texture *ttf_text_;
    TTF_Font *font_;
    int font_size_;
    int font_family_;
};


#endif // _DF_TANKWAR_PAINTER_H