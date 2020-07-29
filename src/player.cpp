#include "player.h"

Player::Player(int id, double x, double y, PlayerData pd)
    : Tank(x, y, id ? SpriteType::PLAYER_2: SpriteType::PLAYER_1),
    data_(pd) {
}

Player::Player(int id, SDL_Point point, PlayerData pd)
    : Tank(point, id ? SpriteType::PLAYER_2: SpriteType::PLAYER_1),
    data_(pd) {
}

Player::~Player() {

}

PlayerData* Player::getdata() {
    return &data_;
}

void Player::try_update(int dt) {
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    is_stop_ = false;
    if (data_.player_id_ == 0) {
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
    data_.score_ += 100;
}

bool Player::respawn() {
    data_.life_count_--;
    if (data_.life_count_ <= 0)
        return true;
    if (data_.player_id_) {
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