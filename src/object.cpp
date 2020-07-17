#include "object.h"
#include "engine.h"

Object::Object(double x, double y, SpriteType type)
    : x_(x), y_(y), type_(type), 
    w_(AppConfig::tile_w), h_(AppConfig::tile_h) {

}

Object::Object(SDL_Point point, SpriteType type)
    : x_(point.x), y_(point.y), type_(type),
    w_(AppConfig::tile_w), h_(AppConfig::tile_h) {

}

Object::~Object() {

}

void Object::try_update(int) {
}

void Object::do_update() {
    // SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
}

bool Object::is_destroy() {
    return false;
}

void Object::draw() {
    Engine *e = Engine::getInstance();
    SDL_Rect objrect = e->getSprite(type_);
    e->draw(objrect, SDL_Rect{x_, y_, w_, h_});
}

// bool intersect(const Object& lhs, const Object& rhs) {
//     double x1 = lhs.getX(); double y1 = lhs.getY();
//     double w1 = lhs.getW(); double h1 = lhs.getH();
//     double x2 = rhs.getX(); double y2 = rhs.getY();
//     double w2 = rhs.getW(); double h2 = rhs.getH();
    
//     if (y1 > y2) {
//         double t1 = x1, t2 = y1, t3 = w1, t4 = h1;
//         x1 = x2; y1 = y2; w1 = w2; h1 = h2;
//         x2 = t1; y2 = t2; w2 = t3; h2 = t4;
//     }
//     if (x2 >= x1) {
//         if (x2 >= x1 + w1 || y2 >= y1 + h1)
//             return false;
//     }
//     if (x2 < x1) {
//         if (x1 >= x2 + w2 || y2 >= y1 + h1)
//             return false;
//     }
//     return true;
// }