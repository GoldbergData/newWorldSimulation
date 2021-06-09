//header

#include "Planet.h"
#include <string>
using namespace std;

//header
Planet::Planet(string color, long capacity, int baseTemperature, Movesets moveset) :
SpaceObject(color, moveset) {
    occupant = nullptr;
    this->capacity = capacity;
    this->baseTemperature = baseTemperature;
}

long Planet::getCapacity() const {
    return capacity;
}

int Planet::getTemperature() const {
    return baseTemperature + 100; //FOR SUN DISTANCE CALC
}

bool Planet::isHabitable() const {
    return true;
}

void Planet::setOccupant(AlienBase* occupant) {
    this->occupant = occupant;
}

AlienBase* Planet::getOccupant() const {
    return occupant;
}

int Planet::getHazard() const { //CAN SET TRIGGER FREQUENCY/CHANCE LATER
    return 0;
}

int Planet::getBonus() const {
    return 0;
}