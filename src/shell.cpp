#include "shell.h"

void Shell::init() {
    w_ = 8;
    h_ = 8;
    speed_ = AppConfig::shell_speed;
    is_destroyed_ = false;
}

Shell::Shell(double x, double y, Direction d)
    : Object(x, y, SpriteType::BULLET), direction_(d) {
    init();
}

Shell::Shell(SDL_Point p, Direction d)
    : Object(p, SpriteType::BULLET), direction_(d) {
    init();
}

Shell::~Shell() {
    
}

void Shell::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect objrect = e->getSprite(type_);
    objrect.x += (int)direction_/4;
    e->draw(objrect, SDL_Rect{x_, y_, w_, h_});
}

bool Shell::check_boundary() {
    if (x_ < 0 || x_ > AppConfig::map_rect.w
        || y_ < 0 || y_ > AppConfig::map_rect.h)
        return false;
    else return true;
}

void Shell::update(int dt) {
    if(!is_destroyed_) {
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
        if (!check_boundary()) {
           destroy();
        }
    }
}

void Shell::destroy() {
    is_destroyed_ = true;
}

bool Shell::is_destroy() {
    return is_destroyed_;
}
