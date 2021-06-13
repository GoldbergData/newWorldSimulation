/**
 * @file RockSlide.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Bare planet class. Did not have time to implement differences.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "RockSlide.h"
#include "Planet.h"
#include <string>
using namespace std;

RockSlide::RockSlide(Movesets moveset) : Planet(moveset) {}

int RockSlide::getHazard() const {
    return rand() % 500;
}

string RockSlide::getName() const {
    return "RockSlide";
}