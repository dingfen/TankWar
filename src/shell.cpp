#include "shell.h"

void Shell::init() {
    w_ = 8;
    h_ = 8;
    speed_ = AppConfig::shell_speed;
    ori_point_ = {x_, y_};
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

void Shell::try_update(int dt) {
    ori_point_ = {x_, y_};
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

void Shell::do_update() {
    if (!check_boundary(this)) {
        destroy();
    }
}

void Shell::destroy() {
    is_destroyed_ = true;
}

bool Shell::is_destroy() {
    return is_destroyed_;
}
