#include "tank.h"

void Tank::init() {
    w_ = 32;
    h_ = 32;
    direction_ = Direction::UP;
    speed_ = AppConfig::tank_speed;
    is_stop_ = false;
    is_destroyed_ = false;
    for(int i = 0; i < AppConfig::max_shell; i++)
        shells.push_back(nullptr);
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

bool Tank::is_destroy() {
    return is_destroyed_;
}

void Tank::draw() {
    Engine *e = Engine::getInstance();

    SDL_Rect srcrect = e->getSprite(type_);
    srcrect.x += (int)direction_;

    e->draw(srcrect, SDL_Rect{x_, y_, w_, h_});
    for(auto& ps : shells) {
        if (ps)
            ps->draw();
    }
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
    for(auto& ps : shells) {
        if (ps) {
            if (ps->is_destroy()) {
                ps.reset();
                ps = nullptr;
            }
            else {
                ps->update(dt);
            }
        }
    }
}

void Tank::fire() {
    int i = 0;
    while(i < AppConfig::max_shell) {
        if (!shells[i]) {
            double x, y;
            switch(direction_) {
                case Direction::UP:
                    x = x_ + (w_ - 8)/2;
                    y = y_;
                    break;
                case Direction::DOWN:
                    x = x_ + (w_ - 8)/2;
                    y = y_ + h_;
                    break;
                case Direction::LEFT:
                    x = x_;
                    y = y_ + (h_ - 8)/2;
                    break;
                case Direction::RIGHT:
                    x = x_ + w_;
                    y = y_ + (h_ - 8)/2;
                    break;
            }
            shells[i].reset(new Shell(x, y, direction_));
            break;
        }
        i++;
    }
}