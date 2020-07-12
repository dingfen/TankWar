#include "water.h"

Water::Water(double x, double y)
    : Object(x, y, SpriteType::WATER) {

}

Water::Water(SDL_Point p)
    : Object(p, SpriteType::WATER) {

}

Water::~Water() {
    
}