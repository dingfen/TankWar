#include "menu.h"
#include "configsheet.h"
#include "engine.h"
#include "store.h"

Menu::Menu()
    : items_({"1 Player", "2 Players", "Config & Help", "Exit"}), 
    pos_y_(ori_pos_y_), is_finished_(false) {

}

Menu::~Menu() {

}

void Menu::draw() {
    Engine *e = Engine::getInstance();
    e->clear();
    // load Logo
    SDL_Rect rect = e->getSprite(SpriteType::TANKS_LOGO);
    SDL_Rect dstrect = AppConfig::logo_rect;
    e->draw(rect, dstrect);

    // load items
    for (int i = 0; i < items_.size(); i++)
        e->writeText(SDL_Point{180, ori_pos_y_+10 + line_spacing_ * i},
            items_[i], SDL_Color{0xff,0xff,0xff,0});
    // load small pointer
    rect = e->getSprite(SpriteType::TANK_A);
    dstrect.x = ori_pos_y_+30; dstrect.y = pos_y_; dstrect.h = dstrect.w = 32;
    e->draw(rect, dstrect);
    e->update();
}

void Menu::update(int dt) {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

void Menu::event(SDL_Event *e) {
    // if event is keyboard
    if (e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_UP:
                if (pos_y_ > ori_pos_y_)
                    pos_y_ -= line_spacing_;
                break;
            case SDLK_DOWN:
                if (pos_y_ < ori_pos_y_ + (items_.size()-1) * line_spacing_)
                    pos_y_ += line_spacing_;
                break;
            case SDLK_ESCAPE:
                break;
            case SDLK_SPACE:
            case SDLK_RETURN:
                this->is_finished_ = true;
                break;
            default: break;
        }
    }
}

bool Menu::finish() {
    return is_finished_;
}

void Menu::nextstate(std::unique_ptr<AppState>& app_state) {
    if (pos_y_ == ori_pos_y_) {
        // 1 Player
        AppConfig::player_nums = 1;
        app_state.reset(new Store());
    } else if (pos_y_ == ori_pos_y_ + line_spacing_) {
        // 2 Players
        AppConfig::player_nums = 2;
        app_state.reset(new Store());
    } else if (pos_y_ == ori_pos_y_ + line_spacing_ * 2) {
        app_state.reset(new ConfigSheet());
    } else
        app_state.reset(nullptr);
}
