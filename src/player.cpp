#include "player.h"

void Player::init(int id) {
    if (id)
        data_ = &AppConfig::p2_data;
    else 
        data_ = &AppConfig::p1_data;
    shells_.clear();
    for(int i = 0; i < data_->max_shell_; i++) {
        shells_.push_back(nullptr);
    }
    speed_ = data_->player_speed_;
}

Player::Player(int id, double x, double y)
    : Tank(x, y, id ? SpriteType::PLAYER_2: SpriteType::PLAYER_1) {
    init(id);
}

Player::Player(int id, SDL_Point point)
    : Tank(point, id ? SpriteType::PLAYER_2: SpriteType::PLAYER_1) {
    init(id);
}

Player::~Player() {

}

PlayerData* Player::getdata() {
    return data_;
}

void Player::boom(int d) {
    data_->health_point_ -= d;
    if (data_->health_point_ <= 0) {
        is_boom_ = true;
        data_->health_point_ = 0;
    }
}

void Player::try_update(int dt) {
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    is_stop_ = false;
    if (data_->player_id_ == 0) {
        if (key_state[SDL_SCANCODE_UP]) {
            direction_ = Direction::UP;
        } else if (key_state[SDL_SCANCODE_DOWN]) {
            direction_ = Direction::DOWN;
        } else if (key_state[SDL_SCANCODE_LEFT]) {
            direction_ = Direction::LEFT;
        } else if (key_state[SDL_SCANCODE_RIGHT]) {
            direction_ = Direction::RIGHT;
        } else {
            is_stop_ = true;
        }
    } else {
        if (key_state[SDL_SCANCODE_W]) {
            direction_ = Direction::UP;
        } else if (key_state[SDL_SCANCODE_S]) {
            direction_ = Direction::DOWN;
        } else if (key_state[SDL_SCANCODE_A]) {
            direction_ = Direction::LEFT;
        } else if (key_state[SDL_SCANCODE_D]) {
            direction_ = Direction::RIGHT;
        } else {
            is_stop_ = true;
        }
    }
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
    } else if (!is_stop_) {
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
    for(auto& ps : shells_) {
        if (ps) {
            ps->try_update(dt);
        }
    }
}

void Player::do_update() {
    if (is_stop_) {
        x_ = ori_point_.x;
        y_ = ori_point_.y;
    }
    Tank::do_update();
}

void Player::addscore() {
    data_->score_ += 100;
}

bool Player::respawn() {
    if (data_->life_count_ > 0)
        data_->life_count_ --;
    else return true;
    data_->health_point_ = data_->sum_hp_;
    if (data_->player_id_) {
        x_ = AppConfig::p2_start_point.x;
        y_ = AppConfig::p2_start_point.y;
        type_ = SpriteType::PLAYER_2;
    } else {
        x_ = AppConfig::p1_start_point.x;
        y_ = AppConfig::p1_start_point.y;
        type_ = SpriteType::PLAYER_1;
    }
    Tank::init();
    return false;
}