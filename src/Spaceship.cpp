//header

#include "Spaceship.h"
#include <string>

Spaceship::Spaceship(AlienBase* occupant) : SpaceObject("TEMP", RANDOM) {
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