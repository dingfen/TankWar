#include "tank.h"

void Tank::init() {
    w_ = 32;
    h_ = 32;
    direction_ = Direction::UP;
    speed_ = AppConfig::tank_speed;
    is_blocked_ = false;
    is_destroyed_ = false;
    ori_point_ = {x_, y_};
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

void Tank::block() {
    is_blocked_ = true;
}

void Tank::nonblock() {
    is_blocked_ = false;
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

void Tank::try_update(int dt) {
    ori_point_ = {x_, y_};
    switch (direction_) {
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
    // shell process
    for(auto& ps : shells) {
        if (ps) {
            ps->try_update(dt);
        }
    }
}

void Tank::do_update() {
    if (is_blocked_) {
        x_ = ori_point_.x;
        y_ = ori_point_.y;
    }
    if (!checkX(this))
        x_ = ori_point_.x;
    if (!checkY(this))
        y_ = ori_point_.y;
        // shell process
    for(auto& ps : shells) {
        if (ps) {
            if (ps->is_destroy()) {
                ps.reset();
                ps = nullptr;
            }
            else {
                ps->do_update();
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