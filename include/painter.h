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

    // draw a Rectangle on render
    // src position in texture png
    // dst position on window
    void drawRect(const SDL_Rect& srcrect, const SDL_Rect& dstrect);

    // write text using color
    void writeText(int x, int y, const std::string&, const SDL_Color&);
private:
    SDL_Renderer *render_;
    SDL_Texture *text_;
    TTF_Font *font_;

};


#endif // _DF_TANKWAR_PAINTER_H