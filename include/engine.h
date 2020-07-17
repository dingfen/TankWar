/*
 * Engine class
 * contains renderer texture spite configer etc.
 * use to wrap SDL API
 * singleton pattern, avoid to get resources again
 */
#ifndef _DF_TANKWAR_ENGINE_H
#define _DF_TANKWAR_ENGINE_H

#include <iostream>
#include "painter.h"

class Engine {
public:
    inline static Engine* getInstance() {
        static Engine e;
        return &e;
    }
    SDL_Window *getWindow() {
        return win_;
    }

    Painter *getPainter() {
        return painter_;
    }

    SDL_Rect getSprite(SpriteType type, int off = 0) {
        SDL_Rect ret = sc_->get(type).rect;
        ret.y += off * ret.h;
        return ret;
    }

    void update();

    // call Painter draw writeText clear
    void clear();
    void draw(const SDL_Rect& srcrect, const SDL_Rect& dstrect);
    void writeText(SDL_Point, const std::string & text, 
        SDL_Color color = {0xff, 0xff, 0xff, 0}, int fontsize = 14, int fontfamily = 0);
    void drawRect(const SDL_Rect& srcrect, SDL_Color color= {0xff, 0xff, 0xff, 0},
        bool is_fill = true);
private:
    Engine();
    Engine(const Engine&);
    Engine& operator=(const Engine&);
    ~Engine();


private:
    SDL_Window *win_;
    Painter *painter_;
    SDL_Surface *loadsuf_;
    SpriteConfig *sc_;
};

#endif // _DF_TANKWAR_ENGINE_H