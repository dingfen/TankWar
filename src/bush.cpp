#include "bush.h"

Bush::Bush(double x, double y)
    : Object(x, y, SpriteType::BUSH) {

}

Bush::Bush(SDL_Point p)
    : Object(p, SpriteType::BUSH) {

}

Bush::~Bush() {
    
}