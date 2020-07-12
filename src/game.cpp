#include "game.h"
#include <fstream>

Game::Game(int stage)
    : stage_(stage), is_finished_(false) {

}


void Game::draw() {

}

void Game::update() {

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
    while(!fin.eof()) {
        std::getline(fin, line);
        std::vector<unique_ptr<Object>> row;
        for(int i = 0; i < line.size(); i++) {
            unique_ptr<Object> obj;
            switch(line.at(i)) {
            case '#' : 
                break;
            case '@' : 
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
    }
}