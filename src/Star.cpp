//header

#include <string>
#include "Star.h"
#include "Orbits.h"

Star::Star() : SpaceObject("yellow", STATIONARY) { //color probably on a star type basis
    temperature = 9000; //CAN UPDATE LATER
}

int Star::getTemperature() const {
    return temperature;
}

string Star::getName() const {
    return "Star";
}