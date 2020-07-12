#include "ice.h"

Ice::Ice(double x, double y)
    : Object(x, y, SpriteType::ICE) {

}

Ice::Ice(SDL_Point p)
    : Object(p, SpriteType::ICE) {

}

Ice::~Ice() {
    
}