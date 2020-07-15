#include "player.h"

void Player::init() {
    score_ = 0;
    is_stop_ = false;
}

Player::Player(int id, double x, double y)
    : player_id_(id),
    Tank(x, y, id ? SpriteType::PLAYER_2: SpriteType::PLAYER_1) {

}

Player::Player(int id, SDL_Point point)
    : player_id_(id),
    Tank(point, id ? SpriteType::PLAYER_2: SpriteType::PLAYER_1) {

}

Player::~Player() {

}

void Player::try_update(int dt) {
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    if (player_id_ == 0) {
        if (key_state[SDL_SCANCODE_UP]) {
            direction_ = Direction::UP;
            is_stop_ = false;
        } else if (key_state[SDL_SCANCODE_DOWN]) {
            direction_ = Direction::DOWN;
            is_stop_ = false;
        } else if (key_state[SDL_SCANCODE_LEFT]) {
            direction_ = Direction::LEFT;
            is_stop_ = false;
        } else if (key_state[SDL_SCANCODE_RIGHT]) {
            direction_ = Direction::RIGHT;
            is_stop_ = false;
        } else {
            is_stop_ = true;
        }
    } else {
        if (key_state[SDL_SCANCODE_W]) {
            direction_ = Direction::UP;
            is_stop_ = false;
        } else if (key_state[SDL_SCANCODE_S]) {
            direction_ = Direction::DOWN;
            is_stop_ = false;
        } else if (key_state[SDL_SCANCODE_A]) {
            direction_ = Direction::LEFT;
            is_stop_ = false;
        } else if (key_state[SDL_SCANCODE_D]) {
            direction_ = Direction::RIGHT;
            is_stop_ = false;
        } else {
            is_stop_ = true;
        }
    }

    Tank::try_update(dt);
}

void Player::do_update() {
    if (is_stop_) {
        x_ = ori_point_.x;
        y_ = ori_point_.y;
    }
    Tank::do_update();
}