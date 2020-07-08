/*
 * Engine class
 * contains renderer texture spite configer etc.
 * singleton pattern, avoid to get resources again
 */
#ifndef _DF_TANKWAR_ENGINE_H
#define _DF_TANKWAR_ENGINE_H

#include <iostream>
#include "appconfig.h"
#include "spriteconfig.h"
#include "exception.h"

class Engine {
public:
    static Engine* getInstance() throw() {
        static Engine e;
        return &e;
    }
    SDL_Window *getWindow() {
        return win_;
    }

    SDL_Renderer *getRenderer() {
        return render_;
    }

    SDL_Texture *getTexture() {
        return text_;
    }

    SDL_Rect getSprite(SpriteType type) {
        return sc_->get(type).rect;
    }

private:
    Engine() throw();
    Engine(const Engine&);
    Engine& operator=(const Engine&);
    ~Engine();


private:
    SDL_Window *win_;
    SDL_Renderer *render_;
    SDL_Texture *text_;
    SDL_Surface *loadsuf_;
    SpriteConfig *sc_;
};

#endif // _DF_TANKWAR_ENGINE_H