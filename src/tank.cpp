#include "tank.h"

void Tank::init() {
    direction_ = Direction::UP;
    speed_ = AppConfig::tank_speed;
    is_stop_ = false;
}

Tank::Tank(double x, double y, SpriteType type)
    : Object(x, y, type) {
    init();
}

Tank::Tank(SDL_Point p, SpriteType type)
    : Object(p, type) {
    init();
}

Tank::~Tank() {
    
}

void Tank::setdirection(Direction d) {
    this->direction_ = d;
}

Direction Tank::getdirection() {
    return this->direction_;
}

void Tank::draw() {
    Engine *e = Engine::getInstance();

    SDL_Rect srcrect = e->getSprite(type_);
    srcrect.x += (int)direction_;

    e->draw(srcrect, SDL_Rect{x_, y_, 32, 32});
}

void Tank::update(int dt) {
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
}