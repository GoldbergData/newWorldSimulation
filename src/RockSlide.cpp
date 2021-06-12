#include "RockSlide.h"
#include "Planet.h"
#include <string>
using namespace std;

RockSlide::RockSlide(Movesets moveset) : Planet(moveset) {}

int RockSlide::getHazard() const {
    return rand() % 500;
}

string RockSlide::getName() const {
    return "RockSlide";
}