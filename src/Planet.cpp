/**
 * @file Planet.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief 
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Planet.h"
#include <string>
using namespace std;


Planet::Planet(Movesets moveset) : SpaceObject(moveset) {
    occupant = nullptr;
    capacity = 1000000;
    baseTemperature = 0;
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

string Planet::getName() const {
    return "Planet";
}