/**
 * @file Spaceship.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief 
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Spaceship.h"
#include <string>

Spaceship::Spaceship(AlienBase* occupant) : SpaceObject(RANDOM) {
    this->occupant = occupant;
    lastMove = NORTH;
}

AlienBase* Spaceship::getOccupant() const {
    return occupant;
}

Moves Spaceship::getLastMove() const {
    return lastMove;
}

void Spaceship::setLastMove(Moves move) {
    lastMove = move;
}