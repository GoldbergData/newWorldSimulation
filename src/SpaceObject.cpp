//header

#include "SpaceObject.h"

SpaceObject::SpaceObject() {
    color = "black";
    moveset = STATIONARY;
}

SpaceObject::SpaceObject(string color, Movesets moveset) {
    this->color = color;
    this->moveset = moveset;
}

bool SpaceObject::isHabitable() const {
    return false;
}

Movesets SpaceObject::getMoveset() const {
    return moveset;
}

string SpaceObject::getColor() const {
    return color;
}

string SpaceObject::getName() const {
    return "SpaceObject";
}