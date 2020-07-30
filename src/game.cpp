#include "game.h"
#include "stone.h"
#include "brick.h"
#include "water.h"
#include "bush.h"
#include "ice.h"
#include "store.h"
#include "menu.h"
#include <algorithm>
#include <random>
#include <fstream>

void Game::init() {
    is_finished_ = 0;
    prepare_time_ = AppConfig::prepare_time;
    over_time_ = AppConfig::game_ending_time;
    hq_destroyed_ = false;
    p1_over_ = false;
    p2_over_ = false;

    enemy_num_ = 20;
    enemy_on_map_ = 0;

    game_over_y_pos_ = AppConfig::window_rect.h;

    if (AppConfig::player_nums == 1) {
        p1.reset(new Player(0, AppConfig::p1_start_point));
        p2.reset();
        p2_over_ = true;
    } else if (AppConfig::player_nums == 2) {
        p1.reset(new Player(0, AppConfig::p1_start_point));
        p2.reset(new Player(1, AppConfig::p2_start_point));
    }
    for(int i = 0; i < AppConfig::max_enemy_nums; i++) {
        enemy_tanks_.push_back(nullptr);
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
    // load the teaser to prepare
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
    drawtank();
    
    drawbush();
    drawbonus();

    if (hq_destroyed_ || (p1_over_ && p2_over_)) {
        e->writeText(SDL_Point{-1, game_over_y_pos_}, "Game Over", SDL_Color{255, 10, 10, 255}, 24);
    }
    e->update();
}

void Game::update(int dt) {
    if (prepare_time_ > 0) {
        prepare_time_ -= dt;
        SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
    } else { 
    if (enemy_num_ <= 0) {
        if (over_time_ > 0) {
            over_time_ -= dt;
        }
        else {
            is_finished_ = 3;
            // win game bonus
            p1->addscore();
            if (p2)
                p2->addscore();
        }
    }
    if(hq_destroyed_ || (p1_over_ && p2_over_)) {
        if (over_time_ > 0) {
            over_time_ -= dt;
            game_over_y_pos_ -= dt * AppConfig::shell_speed;
        }
        else
            is_finished_ = 2;
    }
    try_update_tank(dt);
    try_update_map(dt);
    try_update_bonus(dt);

    boom_detect();
    collision_detect();
    
    do_update_map();
    do_update_tank();
    do_update_bonus();
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
    }
}

void Game::event(SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
        case SDLK_ESCAPE:
            is_finished_ = 1;
            break;
        case SDLK_RCTRL:
            p1->fire();
            break;
        case SDLK_LCTRL:
            if(p2)
                p2->fire();
            break;
        case SDLK_n:
            is_finished_ = 4;
            break;
        default:
            break;
        }
    }
}

bool Game::finish() {
    return this->is_finished_!=0;
}

void Game::nextstate(unique_ptr<AppState>& app_state) {
    switch (is_finished_) {
        case 1:
        case 2:
            AppConfig::current_level = 1;
            app_state.reset(new Menu());
            break;
        case 3:
        case 4:
            app_state.reset(new Store(stage_));
            break;
    }
}

void Game::loadmap() {
    std::ifstream fin;
    fin.open(AppConfig::level_file_path(stage_), std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Cann't open the map " << stage_ << std::endl;
        is_finished_ = 1;
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
            if (auto p = std::dynamic_pointer_cast<Bush>(obj))
                bush_.push_back(p);
            else 
                row.push_back(obj);
        }
        this->map_.push_back(row);
        j++;
    }
    // load headquaters
    map_[0].push_back(shared_ptr<Object>(new Eagle()));
}

void Game::drawmap() {
    for(int i = 0; i < map_.size(); i++)
        for(int j = 0; j < map_[i].size(); j++) {
            if (map_[i][j])
                map_[i][j]->draw();
    }
}

void Game::drawbush() {
    for(auto &p : bush_) {
        p->draw();
    }
}

void Game::drawbonus() {
    for(auto &pb : bonus_)
        if(pb)
            pb->draw();
}

void Game::try_update_map(int dt) {
    for(int i = 0; i < map_.size(); i++)
        for(int j = 0; j < map_[i].size(); j++) {
            if (map_[i][j])
                map_[i][j]->try_update(dt);
    }
}

void Game::try_update_bonus(int dt) {
    for(auto &pb : bonus_) {
        if (pb) {
            pb->try_update(dt);
        }
    }
}

void Game::do_update_map() {
    for(int i = 0; i < map_.size(); i++)
        for(int j = 0; j < map_[i].size(); j++) {
            if (map_[i][j]) {
                if (map_[i][j]->is_destroy() 
                    && !std::dynamic_pointer_cast<Eagle>(map_[i][j])) {
                    map_[i][j].reset();
                    map_[i][j] = nullptr;
                } else {
                    map_[i][j]->do_update();
                }
            }
    }
}

void Game::do_update_bonus() {
    for(auto &pb : bonus_) {
        if (pb) {
            if (pb->is_destroy()) {
                pb.reset();
                pb = nullptr;
            } else {
                pb->do_update();
            }
        }
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
    // draw player info p1
    srcrect = e->getSprite(SpriteType::FLAG);
    const PlayerData* pd = p1->getdata();
    dstrect.x = AppConfig::status_rect.x + 4;
    dstrect.y = 250;
    dstrect.w = 16;
    dstrect.h = 16;
    e->draw(srcrect, dstrect);
    e->writeText(SDL_Point{dstrect.x+20, dstrect.y}, 
        std::to_string(pd->life_count_), {0, 0, 0, 0}, 12);
    dstrect.y += 24;
    dstrect.w = 50;
    dstrect.h = 10;
    e->drawRect(dstrect, {0, 0, 0, 0});
    dstrect.w = 50 * (pd->health_point_) / pd->sum_hp_;
    e->drawRect(dstrect, {0, 255, 0, 0});

    // draw player info p2
    if (p2) {
        srcrect = e->getSprite(SpriteType::FLAG, 1);
        const PlayerData* pd2 = p2->getdata();
        dstrect.y = 300;
        dstrect.w = 16;
        dstrect.h = 16;
        e->draw(srcrect, dstrect);
        e->writeText(SDL_Point{dstrect.x+20, dstrect.y}, 
            std::to_string(pd2->life_count_), {0, 0, 0, 0}, 12);
            dstrect.y += 24;
        dstrect.w = 50;
        dstrect.h = 10;
        e->drawRect(dstrect, {0, 0, 0, 0});
        dstrect.w = 50 * (pd2->health_point_) / pd2->sum_hp_;
        e->drawRect(dstrect, {0, 255, 0, 0});
    }
}

void Game::drawtank() {
    p1->draw();
    if (p2) 
        p2->draw();
    for(auto &t : enemy_tanks_) {
        if(t)
            t->draw();
    }
}

void Game::try_update_tank(int dt) {
    p1->try_update(dt);
    if (p2)
        p2->try_update(dt);
    for(auto &t : enemy_tanks_) {
        if (t)
            t->try_update(dt);
        else if (enemy_num_ - enemy_on_map_ > 0)
            t = generatenemy();
    }
}

void Game::do_update_tank() {
    if (p1->is_destroy())
        p1_over_ = p1->respawn();
    else 
        p1->do_update();

    if (p2)
        if (p2->is_destroy())
            p2_over_ = p2->respawn();
        else 
            p2->do_update();
    
    for(auto &t : enemy_tanks_) {
        if (t) {
            if (t->is_destroy()) {
                t.reset();
                t = nullptr;
            } else {
                t->do_update();
            }
        }
    }
}

shared_ptr<Enemy> Game::generatenemy() {
    srand(time(NULL));
    int i = rand() % 3;
    int t = rand() % 4;
    SDL_Point pos = AppConfig::enemy_start_point(i);
    SpriteType type = (SpriteType)t;
    int level = rand() % 5 -1;
    shared_ptr<Enemy> pe(new Enemy(pos, type, level));

    // check if there has enough space
    for(auto &other : enemy_tanks_) {
        if(tank_tank_collision(pe.get(), other.get())) {
            pe.reset();
            return nullptr;
        }
    }
    if (tank_tank_collision(p1.get(), pe.get())) {
        pe.reset();
        return nullptr;
    }
    if (p2 && tank_tank_collision(p2.get(), pe.get())) {
        pe.reset();
        return nullptr;
    }
    enemy_on_map_++;
    return pe;
}

void Game::collision_detect() {
    vector<bool> p1_blocks(AppConfig::max_enemy_nums, false);
    vector<bool> p2_blocks(AppConfig::max_enemy_nums, false);
    // p1 p2 and map collision
    bool p1_map = tank_map_collision(p1.get());
    bool p2_map = tank_map_collision(p2.get());
    bool p1_p2 = tank_tank_collision(p1.get(), p2.get());

    // p1 p2 and enemy tank collision
    for(int i = 0; i < AppConfig::max_enemy_nums; i++) {
        if (enemy_tanks_[i])
            p1_blocks[i] = tank_tank_collision(p1.get(), enemy_tanks_[i].get());
    }
    for(int i = 0; i < AppConfig::max_enemy_nums; i++) {
        if (enemy_tanks_[i])
            p2_blocks[i] = tank_tank_collision(p2.get(), enemy_tanks_[i].get());
    }
    p1_blocks.push_back(p1_map);
    p1_blocks.push_back(p1_p2);

    p2_blocks.push_back(p2_map);
    p2_blocks.push_back(p1_p2);

    // if all false in p1 block then p1 can move
    if(std::all_of(p1_blocks.begin(), p1_blocks.end(), [](bool v) {return !v;}))
        p1->nonblock();
    else 
        p1->block();

    // if all false in p1 block then p1 can move
    if (p2) {
        if (std::all_of(p2_blocks.begin(), p2_blocks.end(), [](bool v) {return !v;}))
            p2->nonblock();
        else 
            p2->block();
    }

    // if get blocked enemy tank can't move too
    for(int i = 0; i < AppConfig::max_enemy_nums; i++) {
        if (enemy_tanks_[i] == nullptr)
            continue;
        vector<bool> tank_blocks;
        tank_blocks.push_back(tank_map_collision(enemy_tanks_[i].get()));
        for(int j = 0; j < AppConfig::max_enemy_nums; j++) {
            if (i == j) continue;
            tank_blocks.push_back(tank_tank_collision(enemy_tanks_[i].get(), enemy_tanks_[j].get()));
        }
        tank_blocks.push_back(p1_blocks[i]);
        tank_blocks.push_back(p2_blocks[i]);
        if(std::all_of(tank_blocks.begin(), tank_blocks.end(), [](bool v) {return !v;}))
            enemy_tanks_[i]->nonblock();
        else 
            enemy_tanks_[i]->block();
    }
}

bool Game::tank_map_collision(const Tank *p) {
    if (!p)
        return false;
    for(auto &line : map_) {
        for(auto &obj : line) {
            if (obj && !std::dynamic_pointer_cast<Ice>(obj)) {
                SDL_Rect lhs = p->getRect();
                SDL_Rect rhs = obj->getRect();
                // shrink the tank
                // make it easy to pass through the alley
                lhs.x += 2; lhs.y += 2; lhs.w -= 4; lhs.h -= 4;
                if (SDL_HasIntersection(&lhs, &rhs))
                    return true;
            }
        }
    }
    return false;
}

bool Game::tank_tank_collision(const Tank *pt1, const Tank *pt2) {
    if (!pt2 || !pt1)
        return false;
    if (pt1->is_boom() || pt2->is_boom())
        return false;
    SDL_Rect pr1 = pt1->getRect();
    SDL_Rect pr2 = pt2->getRect();
    pr1.x += 2; pr1.y += 2; pr1.w -= 4; pr1.h -= 4;
    pr2.x += 2; pr2.y += 2; pr2.w -= 4; pr2.h -= 4;
    if (SDL_HasIntersection(&pr1, &pr2)) {
        return true;
    }
    else return false;
}

void Game::boom_detect() {
    shell_map_boom(p1.get());
    for(auto & e : enemy_tanks_)
        shell_tank_boom(p1.get(), e.get());
    if (p2) {
        shell_map_boom(p2.get());
        for(auto & e : enemy_tanks_)
            shell_tank_boom(p2.get(), e.get());
    }

    for(auto & e: enemy_tanks_) {
        shell_map_boom(e.get());
        shell_tank_boom(e.get(), p1.get());
        if (p2)
            shell_tank_boom(e.get(), p2.get());
    }

    // shell with shell boom
    for(auto &e : enemy_tanks_) {
        shell_shell_boom(p1.get(), e.get());
        shell_shell_boom(p2.get(), e.get());
    }
}

void Game::shell_map_boom(Tank *t) {
    if (!t)
        return ;
    for(auto &s : t->shells()) {
        if (s && !s->is_boom()) {
            SDL_Rect sherect = s->getRect();
            for(auto &line : map_) {
                for(auto &obj : line) {
                    if (obj) {
                        if(auto p = std::dynamic_pointer_cast<Brick>(obj)) {
                            SDL_Rect objrect = obj->getRect();
                            if (SDL_HasIntersection(&sherect, &objrect)) {
                                s->boom();
                                p->boom(s.get());
                            }
                        }
                        else if(auto p = std::dynamic_pointer_cast<Stone>(obj)) {
                            SDL_Rect objrect = obj->getRect();
                            if (SDL_HasIntersection(&sherect, &objrect)) {
                                s->boom();
                                p->boom(s->damage());
                            }
                        }
                        else if(auto p = std::dynamic_pointer_cast<Eagle>(obj)) {
                            SDL_Rect objrect = obj->getRect();
                            if (SDL_HasIntersection(&sherect, &objrect)) {
                                s->boom();
                                p->boom(s->damage());
                                if(p->is_destroy())
                                    hq_destroyed_ = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Game::shell_tank_boom(Tank *attacker, Tank *victim) {
    if (!victim || !attacker)
        return;
    for(auto &s : attacker->shells()) {
        if (s && !s->is_boom()) {
            SDL_Rect sherect = s->getRect();
            if (!victim->is_boom() && !victim->is_coming()) {
                SDL_Rect objrect = victim->getRect();
                objrect.x += 2; objrect.y += 2; objrect.w -= 4; objrect.h -= 4;
                if (SDL_HasIntersection(&sherect, &objrect)) {
                    s->boom();
                    victim->boom(s->damage());

                    // if victim is enemy and it is boomed then add score
                    if (dynamic_cast<Enemy*>(victim) && victim->is_boom()) {
                        enemy_num_--;
                        enemy_on_map_--;
                        if (auto p = dynamic_cast<Player*>(attacker))
                            p->addscore();
                    }
                }
            }
        }
    }
}

void Game::shell_shell_boom(Tank *us, Tank *en) {
    if (!us || !en)
        return ;
    for(auto &s : us->shells()) {
        if (s && !s->is_boom()) {
            SDL_Rect srect = s->getRect();
            for(auto &b : en->shells()) {
                if (b && !b->is_boom()) {
                    SDL_Rect brect = b->getRect();
                    if (SDL_HasIntersection(&srect, &brect)) {
                        s->boom();
                        b->boom();
                    }
                }
            }
        }
    }
}