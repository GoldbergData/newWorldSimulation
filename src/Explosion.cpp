#include "Explosion.h"
#include <iostream>

Explosion::Explosion() {
    stage = 9;
}

string Explosion::getName() const {
    return "Explosion";
}

int Explosion::getStage() const {
    return stage / 3;
}

void Explosion::decrementStage() {
    stage--;
}