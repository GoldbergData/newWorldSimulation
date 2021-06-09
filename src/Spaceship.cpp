//header

#include "Spaceship.h"
#include <string>

Spaceship::Spaceship(string name) {
    this->name = name;
    move = CENTER;
}

string Spaceship::getName() const {
    return name;
}

Moves Spaceship::getMove() const {
    return move;
}