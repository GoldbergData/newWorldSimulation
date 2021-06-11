#include "ToxicWasteland.h"
#include "Planet.h"
#include <string>
using namespace std;

ToxicWasteland::ToxicWasteland(Movesets moveset) : Planet(moveset) {}

int ToxicWasteland::getHazard() const {
    return 20000;
}

string ToxicWasteland::getName() const {
    return "ToxicWasteland";
}