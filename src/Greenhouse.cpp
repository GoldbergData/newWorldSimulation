#include "Greenhouse.h"
#include "Planet.h"
#include <string>
using namespace std;

Greenhouse::Greenhouse(Movesets moveset) : Planet(moveset) {}

int Greenhouse::getHazard() const {
    return rand() % 500;
}

string Greenhouse::getName() const {
    return "Greenhouse";
}