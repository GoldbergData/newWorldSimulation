//header

#include "SpaceObject.h"

SpaceObject::SpaceObject() {
    color = "black";
}

SpaceObject::SpaceObject(string color, Movesets moveSet) {
    this->color = color;
    this->moveSet = moveSet;
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