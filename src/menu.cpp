#include "menu.h"
#include "engine.h"

Menu::Menu()
    : items_({"1 Player", "2 Players", "Config", "Exit"}), pos_y_(110) {

}

Menu::~Menu() {

}

void Menu::draw() {
    Engine *e = Engine::getInstance();
    e->clear();
    // load Logo
    SDL_Rect rect = e->getSprite(SpriteType::TANKS_LOGO);
    SDL_Rect dstrect = AppConfig::logo_rect;
    e->drawRect(rect, dstrect);

    // load items
    for (int i = 0; i < items_.size(); i++)
        e->writeText(180, 120 + 40 * i, items_[i], SDL_Color{0xff,0xff,0xff,0});
    // load small pointer
    rect = e->getSprite(SpriteType::TANK_A);
    dstrect.x = 140; dstrect.y = pos_y_; dstrect.h = dstrect.w = 32;
    e->drawRect(rect, dstrect);
    e->update();
}

void Menu::update() {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

void Menu::event(SDL_Event *e) {
    // if event is keyboard
    if (e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_UP:
                if (pos_y_ > 110)
                    pos_y_ -= 40;
                break;
            case SDLK_DOWN:
                if (pos_y_ < 230)
                    pos_y_ += 40;
                break;
            case SDLK_ESCAPE:
                break;
            case SDLK_SPACE:
            case SDLK_RETURN:
                break;
            default: break;
        }
    }
}