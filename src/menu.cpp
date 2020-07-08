#include "menu.h"
#include "engine.h"

void Menu::draw() {
    Engine *e = Engine::getInstance();
    SDL_Renderer *render = e->getRenderer();
    SDL_Texture *text = e->getTexture();
    SDL_Rect rect = e->getSprite(SpriteType::TANKS_LOGO);
    SDL_Rect dstrect;
    dstrect.x = 20; 
    dstrect.y = 50; 
    dstrect.h = 72; 
    dstrect.w = 406;
    SDL_RenderCopy(render, text, &rect, &dstrect);
}

void Menu::update() {
    SDL_RenderPresent(Engine::getInstance()->getRenderer());
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}