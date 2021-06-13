/**
 * @file Greenhouse.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Bare planet class. Did not have time to implement differences.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Greenhouse.h"
#include "Planet.h"
#include <string>
using namespace std;

Greenhouse::Greenhouse(Movesets moveset) : Planet(moveset) {}

int Greenhouse::getHazard() const {
    return rand() % 500;
}

string Greenhouse::getName() const {
    return "Greenhouse";
}