#include "menu.h"
#include "engine.h"

void Menu::draw() {
    Engine *e = Engine::getInstance();
    Painter *p = e->getPainter();

    // load Logo
    SDL_Rect rect = e->getSprite(SpriteType::TANKS_LOGO);
    SDL_Rect dstrect;
    dstrect.x = 20; 
    dstrect.y = 50; 
    dstrect.h = 72; 
    dstrect.w = 406;
    p->drawRect(rect, dstrect);

    // load items
    // for(int i = 0; i < items.size(); i++) {
        
    // }
}

void Menu::update() {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}