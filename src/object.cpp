#include "object.h"
#include "engine.h"

Object::Object(double x, double y, SpriteType type)
    : x_(x), y_(y), type_(type) {
        obj_rect_ = SpriteConfig::getInstance()->get(type).rect;
}

Object::Object(SDL_Point point, SpriteType type)
    : x_(point.x), y_(point.y) {
        obj_rect_ = SpriteConfig::getInstance()->get(type).rect;

}

Object::~Object() {

}

void Object::update(int) {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

void Object::draw() {
    Engine *e = Engine::getInstance();

    e->draw(obj_rect_, SDL_Rect{x_, y_, AppConfig::tile_w, AppConfig::tile_h});
}