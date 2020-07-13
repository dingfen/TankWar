#include "object.h"
#include "engine.h"

Object::Object(double x, double y, SpriteType type)
    : x_(x), y_(y), type_(type) {

}

Object::Object(SDL_Point point, SpriteType type)
    : x_(point.x), y_(point.y) {

}

Object::~Object() {

}

void Object::update(int) {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

void Object::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect obj_rect_ = e->getSprite(type_);
    e->draw(obj_rect_, SDL_Rect{x_, y_, AppConfig::tile_w, AppConfig::tile_h});
}