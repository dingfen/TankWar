#include "brick.h"
#include "shell.h"

Brick::Brick(double x, double y)
    : Object(x, y, SpriteType::BRICK_WALL), texture_off_(0),
    is_destroyed_(false), health_point_(AppConfig::brick_hp) {
}

Brick::Brick(SDL_Point p)
    : Object(p, SpriteType::BRICK_WALL), texture_off_(0),
    is_destroyed_(false), health_point_(AppConfig::brick_hp) {
}

Brick::~Brick() {
    
}

void Brick::breakdown(int to) {
    texture_off_ = to;
    switch (texture_off_)
    {
    case 0:
        break;
    case 1:
        h_ = 8;
        break;
    case 2: 
        x_ += 8; w_ = 8;
        break;
    case 3:
        y_ += 8; h_ = 8;
        break;
    case 4:
        w_ = 8;
        break;
    case 5:
        x_ += 8; h_ = 8; w_ = 8;
        break;
    case 6:
        x_ += 8; y_ += 8; h_ = 8; w_ = 8;
        break;
    case 7:
        h_ = 8; w_ = 8;
        break;
    case 8:
        y_ += 8; h_ = 8; w_ = 8;
        break;
    }
}

void Brick::boom(Shell *s) {
    health_point_ -= s->damage();
    if (health_point_ <= 0) {
        health_point_ = 0;
        if (s->getlevel() < 1) {
        switch(texture_off_) {
            case 0:
                switch (s->getdirection()) {
                case Direction::UP: breakdown(1); break;
                case Direction::DOWN: breakdown(3); break;
                case Direction::LEFT: breakdown(4); break;
                case Direction::RIGHT: breakdown(2); break;
                }
                break;
            case 1:
                switch (s->getdirection()) {
                case Direction::UP: 
                case Direction::DOWN: is_destroyed_ = true; break;
                case Direction::LEFT: breakdown(7); break;
                case Direction::RIGHT: breakdown(5); break;
                }
                break;
            case 2:
                switch (s->getdirection()) {
                case Direction::UP: breakdown(5); break;
                case Direction::DOWN: breakdown(6); break;
                case Direction::LEFT:
                case Direction::RIGHT: is_destroyed_ = true; break;
                }
                break;
            case 3:
                switch (s->getdirection())
                {
                case Direction::UP:
                case Direction::DOWN: is_destroyed_ = true; break;
                case Direction::LEFT: breakdown(8); break;
                case Direction::RIGHT: breakdown(6); break;
                }
                break;
            case 4:
                switch (s->getdirection())
                {
                case Direction::UP: breakdown(7); break;
                case Direction::DOWN: breakdown(8); break;
                case Direction::LEFT:
                case Direction::RIGHT: is_destroyed_ = true; break;
                }
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                is_destroyed_ = true;
                break;
        }
        } else {
            is_destroyed_ = true;
        }
    }
}

bool Brick::is_destroy() {
    return is_destroyed_;
}