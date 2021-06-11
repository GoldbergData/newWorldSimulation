//header

#include <string>
#include "Star.h"
#include "Orbits.h"

Star::Star() : SpaceObject(STATIONARY) { //color probably on a star type basis
    temperature = 9000; //CAN UPDATE LATER
    filename = getName() + to_string(rand() % 5) + ".png";
}

int Star::getTemperature() const {
    return temperature;
}

string Star::getName() const {
    return "Star";
}

string Star::getFilename() const {
    return filename;
}