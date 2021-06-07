//header

#include "SpaceObject.h"

SpaceObject::SpaceObject() {
    color = "black";
}

SpaceObject::SpaceObject(string color) {
    this->color = color;
}

bool SpaceObject::isHabitable() const {
    return false;
}

string SpaceObject::getColor() const {
    return color;
}

string SpaceObject::toString() const {
    return "SpaceObject";
}