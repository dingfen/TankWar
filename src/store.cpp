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

void Store::show_money(int i, SDL_Rect icon) {
    Engine *e = Engine::getInstance();
    SDL_Rect player;
    if (i == 0) {
        player = e->getSprite(SpriteType::PLAYER_1);
    } else {
        player = e->getSprite(SpriteType::PLAYER_2);
    }
    icon.y += i * 40;
    e->draw(player, icon);
}

void Store::draw() {
    Engine *e = Engine::getInstance();
    e->clear();
    // load title
    e->writeText(SDL_Point{-1, 30}, "Stage 1");

    // load line
    SDL_Rect rect = middle(4, 200);
    rect.y = 60;
    e->drawRect(rect);
    // load players' money
    for(int i = 0; i < AppConfig::player_nums; i++)
        show_money(i, SDL_Rect{120, 80, 32, 32});

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

void Store::nextstate(std::unique_ptr<AppState>& app_state) {
    
}
