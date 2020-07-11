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
    SDL_Point p;
    p.x = icon.x + 150;
    p.y = icon.y + 10;
    e->writeText(p, "1000 $ ", SDL_Color{0xff, 200, 0, 0});
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

    // load goods_
    for(int i = 0; i < goods_.size(); i++)
        e->writeText(SDL_Point{60, 170+i*line_spacing_}, goods_[i]);
    // write tips
    e->writeText(SDL_Point{30, 400}, "\'Space\' to Buy", 
        SDL_Color{0xff, 0xff, 0, 0}, 12);
    e->writeText(SDL_Point{300, 400}, "\'Enter\' -->", 
        SDL_Color{0xff, 0xff, 0, 0}, 12);
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
    : goods_({"More Life * 1",
    "Deep Damage * 1",
    "More Shield time * 1",
    "Less Enemy * 1"}),
    is_finished_(false) {

}

Store::~Store() {

}

void Store::nextstate(std::unique_ptr<AppState>& app_state) {

}
