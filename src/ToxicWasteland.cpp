#include "ToxicWasteland.h"
#include "Planet.h"
#include <string>
using namespace std;

ToxicWasteland::ToxicWasteland(Movesets moveset) : Planet(moveset) {}

int ToxicWasteland::getHazard() const {
    return rand() % 500;
}

string ToxicWasteland::getName() const {
    return "ToxicWasteland";
}