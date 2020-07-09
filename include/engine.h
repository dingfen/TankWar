/*
 * Engine class
 * contains renderer texture spite configer etc.
 * singleton pattern, avoid to get resources again
 */
#ifndef _DF_TANKWAR_ENGINE_H
#define _DF_TANKWAR_ENGINE_H

#include <iostream>
#include "painter.h"

class Engine {
public:
    inline static Engine* getInstance() throw() {
        static Engine e;
        return &e;
    }
    SDL_Window *getWindow() {
        return win_;
    }

    Painter *getPainter() {
        return painter_;
    }

    SDL_Rect getSprite(SpriteType type) {
        return sc_->get(type).rect;
    }

    void update();

    // call Painter drawRect writeText
    void drawRect(const SDL_Rect& srcrect, const SDL_Rect& dstrect);
    void writeText(int x, int y, const std::string & text, SDL_Color color);
private:
    Engine() throw();
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