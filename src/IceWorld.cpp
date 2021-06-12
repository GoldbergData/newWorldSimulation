#include "IceWorld.h"
#include "Planet.h"
#include <string>
using namespace std;

IceWorld::IceWorld(Movesets moveset) : Planet(moveset) {}

int IceWorld::getHazard() const {
    return rand() % 500;
}

string IceWorld::getName() const {
    return "IceWorld";
}