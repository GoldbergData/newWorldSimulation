#include "PurpleGas.h"
#include "Planet.h"
#include <string>
using namespace std;

PurpleGas::PurpleGas(Movesets moveset) : Planet(moveset) {}

int PurpleGas::getHazard() const {
    return rand() % 500;
}

string PurpleGas::getName() const {
    return "PurpleGas";
}