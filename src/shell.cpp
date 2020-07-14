#include "shell.h"

void Shell::init() {
    speed_ = AppConfig::shell_speed;
    is_stop_ = false;
}

Shell::Shell(double x, double y, Direction d)
    : Object(x, y, SpriteType::BULLET), direction_(d) {

}

Shell::Shell(SDL_Point p, Direction d)
    : Object(p, SpriteType::BULLET), direction_(d) {

}

Shell::~Shell() {
    
}

void Shell::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect objrect = e->getSprite(type_);
    e->draw(objrect, SDL_Rect{x_, y_, 8, 8});
}

void Shell::update(int dt) {
    if(!is_stop_) {
        switch (direction_)
        {
        case Direction::UP:
            y_ -= dt * speed_;
            break;
        case Direction::DOWN:
            y_ += dt * speed_;
            break;
        case Direction::LEFT:
            x_ -= dt * speed_;
            break;
        case Direction::RIGHT:
            x_ += dt * speed_;
            break;
        default:
            break;
        }
    }
    if (!check_boundary()) {
        is_stop_ = true;
    }
}
