#include "object.h"
#include "engine.h"

Object::Object(double x, double y, SpriteType type)
    : x_(x), y_(y), type_(type), 
    w_(AppConfig::tile_w), h_(AppConfig::tile_h) {

}

Object::Object(SDL_Point point, SpriteType type)
    : x_(point.x), y_(point.y), 
    w_(AppConfig::tile_w), h_(AppConfig::tile_h) {

}

Object::~Object() {

}

void Object::update(int) {
    SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

void Object::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect objrect = e->getSprite(type_);
    e->draw(objrect, SDL_Rect{x_, y_, w_, h_});
}
