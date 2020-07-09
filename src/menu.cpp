#include "menu.h"
#include "engine.h"

Menu::Menu()
    : items({"1 Player", "2 Players", "Config", "Exit"}) {

}

Menu::~Menu() {

}

void Menu::draw() {
    Engine *e = Engine::getInstance();

    // load Logo
    SDL_Rect rect = e->getSprite(SpriteType::TANKS_LOGO);
    SDL_Rect dstrect = AppConfig::logo_rect;
    e->drawRect(rect, dstrect);

    // load items
    for (int i = 0; i < items.size(); i++)
        e->writeText(180, 120 + 40 * i, items[i], SDL_Color{0xff,0xff,0xff,0});

    e->update();
}

void Menu::update() {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}