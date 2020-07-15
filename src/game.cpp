#include "game.h"
#include "stone.h"
#include "brick.h"
#include "water.h"
#include "bush.h"
#include "ice.h"
#include <fstream>

void Game::init() {
    is_finished_ = false;
    prepare_time_ = AppConfig::prepare_time;
    enemy_num_ = 20;
    if (AppConfig::player_nums == 1) {
        p1.reset(new Player(0, 0, 0));
        p2.reset();
    } else if (AppConfig::player_nums == 2) {
        p1.reset(new Player(0, 0, 0));
        p2.reset(new Player(1, 0, 32));
    }
    loadmap();
}

Game::Game(int stage)
    : stage_(stage) {
    init();
}

Game::~Game() {
    
}


void Game::draw() {
    Engine *e = Engine::getInstance();
    e->clear();
    // load the teaser
    if (prepare_time_ > 0) {
        std::string text = "STAGE " + std::to_string(stage_);
        e->writeText(SDL_Point{-1, -1}, text, SDL_Color{0xff, 0xff, 0, 0}, 20);
        e->update();
        return ;
    }
    // load Game map and Draw it
    drawmap();
    // load status
    drawstatus();
    p1->draw();
    if (p2) 
        p2->draw();
    
    e->update();
}

void Game::update(int dt) {
    if (prepare_time_ > 0) {
        prepare_time_ -= dt;
        SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
    } else {
        p1->try_update(dt);
        if (p2)
            p2->try_update(dt);

        bool collision_map = collision_detect();
        if (collision_map) {
            p1->block();
        }
        else p1->nonblock();

        p1->do_update();
        if (p2)
            p2->do_update();
        SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
    }
}

void Game::event(SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
        case SDLK_ESCAPE:
            is_finished_ = true;
            break;
        case SDLK_RCTRL:
            p1->fire();
            break;
        case SDLK_LCTRL:
            if(p2)
                p2->fire();
            break;
        default:
            break;
        }
    }
}

bool Game::finish() {
    return this->is_finished_;
}

void Game::nextstate(std::unique_ptr<AppState>& app_state) {
    app_state.release();
}

void Game::loadmap() {
    std::ifstream fin;
    fin.open(AppConfig::level_file_path(stage_), std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Cann't open the map " << stage_ << std::endl;
        is_finished_ = true;
        return;
    }
    std::string line;
    int i, j = 0;
    while(!fin.eof()) {
        std::getline(fin, line);
        vector<shared_ptr<Object>> row;
        for(i = 0; i < line.size(); i++) {
            shared_ptr<Object> obj = nullptr;
            switch(line.at(i)) {
            case '#' : 
                obj = shared_ptr<Object>(new Brick(i * AppConfig::tile_w, j * AppConfig::tile_h));
                break;
            case '@' :
                obj = shared_ptr<Object>(new Stone(i * AppConfig::tile_w, j * AppConfig::tile_h));
                break;
            case '%' :
                obj = shared_ptr<Object>(new Bush(i * AppConfig::tile_w, j * AppConfig::tile_h));
                break;
            case '~' :
                obj = shared_ptr<Object>(new Water(i * AppConfig::tile_w, j * AppConfig::tile_h));
                break;
            case '-' :
                obj = shared_ptr<Object>(new Ice(i * AppConfig::tile_w, j * AppConfig::tile_h));
                break;
            default: obj = nullptr;
            }
            row.push_back(obj);
        }
        this->map_.push_back(row);
        j++;
    }
}

void Game::drawmap() {
    for(int i = 0; i < map_.size(); i++)
        for(int j = 0; j < map_[i].size(); j++) {
            if (map_[i][j])
                map_[i][j]->draw();
    }
}

void Game::drawstatus() {
    Engine *e = Engine::getInstance();
    SDL_Rect dstrect;
    // paint gray
    dstrect = AppConfig::status_rect;
    e->drawRect(dstrect, SDL_Color{0xA0,0xA0,0xA0,0}, true);
    
    // draw left enemy
    SDL_Rect srcrect = e->getSprite(SpriteType::LEFT_ENEMY);
    for(int i = 0; i < enemy_num_; i++) {
        dstrect.x = AppConfig::status_rect.x + 8 + srcrect.w * (i % 2);
        dstrect.y = 5 + srcrect.h * (i / 2);
        dstrect.h = srcrect.h;
        dstrect.w = srcrect.w;
        e->draw(srcrect, dstrect);
    }
    // draw stage info
    srcrect = e->getSprite(SpriteType::STAGE_STATUS);
    dstrect.x = AppConfig::status_rect.x + 8;
    dstrect.y = 180;
    dstrect.w = srcrect.w;
    dstrect.h = srcrect.h;
    e->draw(srcrect, dstrect);
    e->writeText(SDL_Point{dstrect.x+8, dstrect.y+40}, 
        std::to_string(stage_), SDL_Color{0, 0, 0, 0});
}

bool Game::collision_detect() {
    SDL_bool in = SDL_FALSE;
    for(auto &line : map_) {
        for(auto &obj : line) {
            if (obj) {
                SDL_Rect lhs = p1->getRect();
                SDL_Rect rhs = obj->getRect();
                in = SDL_HasIntersection(&lhs, &rhs);
                if (in) return in;
            }
        }
    }
    return false;
}