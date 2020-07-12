#include "game.h"
#include "stone.h"
#include "brick.h"
#include <fstream>

Game::Game(int stage)
    : stage_(stage), is_finished_(false),
    prepare_time_(AppConfig::prepare_time) {

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
    loadmap();


    e->update();
}

void Game::update(int dt) {
    if (prepare_time_ > 0) {
        prepare_time_ -= dt;
        SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
    } else {
        SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
    }
}

void Game::event(SDL_Event *e) {

}

bool Game::finish() {
    return this->is_finished_;
}

void Game::nextstate(std::unique_ptr<AppState>& app_state) {

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
                break;
            case '~' :
                break;
            case '-' :
                break;
            default: obj = nullptr;
            }
            row.push_back(obj);
        }
        this->map_.push_back(row);
        j++;
    }

    for(i = 0; i < map_.size(); i++)
        for(j = 0; j < map_[i].size(); j++) {
            if (map_[i][j])
                map_[i][j]->draw();
        }
}