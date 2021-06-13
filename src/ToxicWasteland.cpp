/**
 * @file ToxicWasteland.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Bare planet class. Did not have time to implement differences.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ToxicWasteland.h"
#include "Planet.h"
#include <string>
using namespace std;

ToxicWasteland::ToxicWasteland(Movesets moveset) : Planet(moveset) {}

int ToxicWasteland::getHazard() const {
    return rand() % 500;
}

string ToxicWasteland::getName() const {
    return "ToxicWasteland";
}