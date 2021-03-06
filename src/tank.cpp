#include "tank.h"
#include "player.h"

void Tank::init() {
    w_ = 32;
    h_ = 32;
    direction_ = Direction::UP;
    
    is_blocked_ = false;
    is_destroyed_ = false;
    is_boom_ = false;
    is_coming_ = true;
    kind_ = 0;

    flash_cycle_ = 0;
    texture_off_ = 0;
    ori_point_ = {x_, y_};
    shells_.clear();
    for(int i = 0; i < AppConfig::max_shell; i++)
        shells_.push_back(nullptr);
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

void Tank::destroy() {
    is_destroyed_ = true;
}

bool Tank::is_destroy() {
    return is_destroyed_;
}

void Tank::boom(int d) {
    health_point_ -= d;
    if (health_point_ <= 0) {
        is_boom_ = true;
        health_point_ = 0;
    }
}

bool Tank::is_boom() const{
    return is_boom_;
}

bool Tank::is_coming() const {
    return is_coming_;
}

int Tank::getkind() const {
    return kind_;
}

void Tank::settanklevel(int l) {
    if (l > 2) 
        l = 2;
    else if (l < 0) {
        l = 0;
    }
    tank_level_ = l;
    switch (tank_level_) {
    case 0:
        speed_ = 0.08;
        health_point_ = 20;
        break;
    case 1:
        speed_ = 0.10;
        health_point_ = 30;
        break;
    case 2:
        speed_ = 0.12;
        health_point_ = 40;
        break;
    }
}

void Tank::setshellevel(int l) {
    if (l > 2) 
        l = 2;
    else if (l < 0) {
        l = 0;
    }
    shell_level_ = l;
}

int Tank::getlevel() {
    return tank_level_;
}

int Tank::getshellevel() {
    return shell_level_;
}

void Tank::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect srcrect;
    if (is_boom_) {
        // has been boomed, collision with shell
        type_ = SpriteType::DESTROY_TANK;
        srcrect = e->getSprite(type_, texture_off_);
        w_ = 64;
        h_ = 64;
        e->draw(srcrect, SDL_Rect{x_-16, y_-16, w_, h_});
    } else if (is_coming_){
        // cooming soon
        srcrect = e->getSprite(SpriteType::CREATE, texture_off_);
        e->draw(srcrect, SDL_Rect{x_, y_, w_, h_});
    } else {
        // normal condition
        SDL_Rect srcrect = e->getSprite(type_, 0, kind_);
        srcrect.x += (int)direction_;
        srcrect.y += tank_level_ * 64;
        e->draw(srcrect, SDL_Rect{x_, y_, w_, h_});
    }
    for(auto& ps : shells_) {
        if (ps)
            ps->draw();
    }
}

void Tank::try_update(int dt) {
    if (is_boom_) {
        flash_cycle_ += dt;
        if (flash_cycle_ > boom_flicker) {
            texture_off_ ++;
            flash_cycle_ = 0;
        }
    } else if (is_coming_) {
        flash_cycle_ += dt;
        if (flash_cycle_ > coming_flicker) {
            texture_off_ ++;
            flash_cycle_ = 0;
        }
    } else {
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
    }
    // shell process
    for(auto& ps : shells_) {
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
    bool shell_flying = false;
    for(auto& ps : shells_) {
        if (ps) {
            shell_flying = true;
            if (ps->is_destroy()) {
                ps.reset();
                ps = nullptr;
            }
            else {
                ps->do_update();
            }
        }
    }
    if (is_boom_ && !shell_flying && texture_off_ > 6) {
        destroy();
    }
    if (is_coming_ && texture_off_ > 9) {
        is_coming_ = false;
        flash_cycle_ = 0;
        texture_off_ = 0;
    }
}

void Tank::fire() {
    if (is_boom_ || is_coming_)
        return ;

    for(auto &s : shells_) {
        if (!s) {
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
            s.reset(new Shell(x, y, direction_, shell_level_));
            break;
        }
    }
}

std::vector<std::shared_ptr<Shell>>& Tank::shells() {
    return shells_;
}