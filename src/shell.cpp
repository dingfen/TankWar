#include "shell.h"

void Shell::init(int l) {
    w_ = 8;
    h_ = 8;
    setlevel(l);
    ori_point_ = {x_, y_};
    is_destroyed_ = false;
    is_boom_ = false;
    flash_cycle_ = 0;
    texture_off_ = 0;
}

Shell::Shell(double x, double y, Direction d, int l)
    : Object(x, y, SpriteType::BULLET), direction_(d) {
    init(l);
}

Shell::Shell(SDL_Point p, Direction d, int l)
    : Object(p, SpriteType::BULLET), direction_(d) {
    init(l);
}

Shell::~Shell() {
    
}

int Shell::getlevel() {
    return level_;
}

void Shell::setlevel(int l) {
    level_ = l;
    switch (level_) {
    case 0:
        damage_ = 20;
        speed_ = 0.20;
        break;
    case 1:
        damage_ = 30;
        speed_ = 0.25;
        break;
    case 2:
        damage_ = 40;
        speed_ = 0.30;
        break;
    }
}

void Shell::setdamage(int d) {
    damage_ = d;
}

int Shell::damage() {
    return damage_;
}

void Shell::setspeed(int s) {
    speed_ = s;
}

Direction Shell::getdirection() {
    return direction_;
}

void Shell::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect objrect;
    if (is_boom_) {
        type_ = SpriteType::DESTROY_BULLET;
        objrect = e->getSprite(type_, texture_off_);
        w_ = 32;
        h_ = 32;
        e->draw(objrect, SDL_Rect{x_-12, y_-12, w_, h_});
    } else {
        objrect = e->getSprite(type_);
        objrect.x += (int)direction_/4;
        e->draw(objrect, SDL_Rect{x_, y_, w_, h_});
    }
}

void Shell::try_update(int dt) {
    if (!is_boom_) {
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
    } else {
        flash_cycle_ += dt;
        if (flash_cycle_ > shell_flicker) {
            texture_off_ ++;
            flash_cycle_ = 0;
        }
    }
}

void Shell::do_update() {
    if (texture_off_ > 4 || !check_boundary(this)) {
        destroy();
    }
}

void Shell::destroy() {
    is_destroyed_ = true;
}

bool Shell::is_destroy() {
    return is_destroyed_;
}

void Shell::boom() {
    is_boom_ = true;
}

bool Shell::is_boom() {
    return is_boom_;
}