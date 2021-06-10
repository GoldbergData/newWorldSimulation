#include "Explosion.h"

Explosion::Explosion() {
    image = "ExplosionBig";
}

string Explosion::getName() const {
    return "Explosion";
}

void Explosion::setImage(string filename) {
    image = filename;
}