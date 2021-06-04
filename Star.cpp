//header

#include <string>
#include "Star.h"

Star::Star() : SpaceObject("yellow") {
    temperature = 9000; //CAN UPDATE LATER
}

int Star::getTemperature() const{
    return temperature;
}
