#include "store.h"
#include "engine.h"

inline SDL_Rect middle(int h = 32, int w = 32) {
    SDL_Rect p;
    p.x = (AppConfig::window_rect.w - w) / 2;
    p.y = (AppConfig::window_rect.h - h) / 2;
    p.h = h;
    p.w = w;
    return p;
}

void Store::draw() {
    Engine *e = Engine::getInstance();
    e->clear();
    // load title
    e->writeText(SDL_Point{-1, 30}, "Stage 1");

    // load line
    e->drawRect();
    // load players' money
    e->update();
}

void Store::update() {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

bool Store::finish() {
    return is_finished_;
}

void Store::event(SDL_Event *e) {

}

Store::Store()
    : goods_({"More Life * 1", "Deep Damage"}),
    is_finished_(false) {

}

Store::~Store() {

}