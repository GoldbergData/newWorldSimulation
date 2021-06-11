//header

#include "SpaceObject.h"

SpaceObject::SpaceObject() {
    moveset = STATIONARY;
}

SpaceObject::SpaceObject(Movesets moveset) {
    this->moveset = moveset;
}

bool SpaceObject::isHabitable() const {
    return false;
}

Movesets SpaceObject::getMoveset() const {
    return moveset;
}

string SpaceObject::getName() const {
    return "SpaceObject";
}