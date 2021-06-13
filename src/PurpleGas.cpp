/**
 * @file PurpleGas.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Bare planet class. Did not have time to implement differences.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
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