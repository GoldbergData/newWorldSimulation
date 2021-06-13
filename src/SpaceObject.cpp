/**
 * @file SpaceObject.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief 
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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