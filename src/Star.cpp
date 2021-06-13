/**
 * @file Star.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include "Star.h"
#include "Orbits.h"

Star::Star() : SpaceObject(STATIONARY) {
    temperature = 9000;
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