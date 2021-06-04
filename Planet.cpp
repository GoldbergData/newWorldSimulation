//header

#include "Planet.h"
#include <string>
using namespace std;

//header
Planet::Planet(string color, int capacity, int baseTemperature) : SpaceObject(color) {
    this->capacity = capacity;
    this->baseTemperature = baseTemperature;
}

int Planet::getCapacity() {
    return capacity;
}

int Planet::getTemperature() {
    return baseTemperature + 100; //FOR SUN DISTANCE CALC
}

bool Planet::isHabitable() {
    return true;
}

void Planet::setOccupant(AlienBase* occupant) {
    this->occupant = occupant;
}

int Planet::getHazard() { //CAN SET TRIGGER FREQUENCY/CHANCE LATER
    return 0;
}

int Planet::getBonus() {
    return 0;
}
