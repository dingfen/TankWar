#include "object.h"

Object::Object(double x, double y, SpriteType type)
    : x_(x), y_(y), type_(type) {
        obj_rect_ = SpriteConfig::getInstance()->get(type);
}

Object::Object(SDL_Point point, SpriteType type) {

}