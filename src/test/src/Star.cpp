//header

#include <string>
#include "Star.h"

Star::Star() : SpaceObject("yellow") { //color probably on a star type basis
    temperature = 9000; //CAN UPDATE LATER
}

int Star::getTemperature() const{
    return temperature;
}