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
    SDL_Rect objrect = e->getSprite(type_);
    e->draw(objrect, SDL_Rect{x_, y_, AppConfig::tile_w, AppConfig::tile_h});
}

inline bool Object::check_boundary() {
    if (x_ < 0 || x_ > AppConfig::map_rect.w 
        || y_ < 0 || y_ > AppConfig::map_rect.h)
        return false;
    else return true;
}