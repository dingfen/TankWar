#include "store.h"
#include "engine.h"
#include "game.h"
#include "menu.h"

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
    std::string score;
    std::string life;
    if (i == 0) {
        player = e->getSprite(SpriteType::PLAYER_1);
        score = std::to_string(pd1.score_) + " $ ";
        life = "x "+ std::to_string(pd1.life_count_);
    } else {
        player = e->getSprite(SpriteType::PLAYER_2);
        score = std::to_string(pd2.score_) + " $ ";
        life = "x " + std::to_string(pd2.life_count_);
    }
    icon.y += i * 40;
    e->draw(player, icon);
    SDL_Point p;
    p.x = icon.x + 50;
    p.y = icon.y + 10;
    e->writeText(p, life, SDL_Color{0xf0, 0xff, 0xf0, 0});
    p.x = icon.x + 150;
    e->writeText(p, score, SDL_Color{0xff, 200, 0, 0});
}

void Store::draw() {
    Engine *e = Engine::getInstance();
    e->clear();
    // load title
    std::string text = "Stage " + std::to_string(stage_);
    e->writeText(SDL_Point{-1, 30}, text);

    // load line
    SDL_Rect rect = middle(4, 200);
    rect.y = 60;
    e->drawRect(rect);
    // load players' money
    for(int i = 0; i < player_nums; i++)
        show_money(i, SDL_Rect{120, 80, 32, 32});

    // load cursor
    e->drawRect(SDL_Rect{20, cursor_pos_+p1_offset_*line_spacing_, 10, 10},
        SDL_Color{0xff, 0xff, 0, 0});
    if (player_nums > 1) {
        e->drawRect(SDL_Rect{40, cursor_pos_+p2_offset_*line_spacing_, 10, 10},
            SDL_Color{0x00, 0xff, 0, 0});
    }
    // load goods_
    for(int i = 0; i < goods_.size(); i++)
        e->writeText(SDL_Point{60, cursor_pos_+i*line_spacing_}, goods_[i]);
    // write tips
    e->writeText(SDL_Point{30, 400}, "\'Space\' to Buy", 
        SDL_Color{0xff, 0xff, 0, 0}, 12);
    e->writeText(SDL_Point{300, 400}, "\'Enter\' -->", 
        SDL_Color{0xff, 0xff, 0, 0}, 12);
    e->update();
}

void Store::update(int dt) {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

bool Store::finish() {
    return is_finished_;
}

void Store::event(SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
        case SDLK_UP:
            if (p1_offset_ > 0)
                p1_offset_ --;
            else 
                p1_offset_ = goods_.size()-1;
            break;
        case SDLK_DOWN:
            if (p1_offset_ < goods_.size()-1)
                p1_offset_++;
            else
                p1_offset_ = 0;
            break;
        case SDLK_w:
            if (p2_offset_ > 0)
                p2_offset_ --;
            else 
                p2_offset_ = goods_.size()-1;
            break;
        case SDLK_s:
            if (p2_offset_ < goods_.size()-1)
                p2_offset_++;
            else
                p2_offset_ = 0;
            break;
        case SDLK_SPACE:
            break;
        case SDLK_RETURN:
            is_finished_ = true;
            break;
        default:
            break;
        }
    }

}

Store::Store(int stage, const PlayerData *p1, const PlayerData *p2)
    : goods_({"More Life * 1",
    "Deep Damage * 1",
    "More Shield time * 1",
    "Less Enemy * 1"}),
    is_finished_(false), stage_(stage) {
    player_nums = AppConfig::player_nums;
    cursor_pos_ = 170;
    p1_offset_ = 0;
    p2_offset_ = 0;
    if (p1) {
        pd1 = *p1;
    }
    if (p2) {
        pd2 = *p2;
    }
}

Store::~Store() {

}

void Store::nextstate(std::unique_ptr<AppState>& app_state) {
    if (AppConfig::current_level > 35) {
        app_state.reset(new Menu());
    } else {
        if (player_nums > 1)
            app_state.reset(new Game(AppConfig::current_level++, &pd1, &pd2));
        else 
            app_state.reset(new Game(AppConfig::current_level++, &pd1));
    }
}
