/**
 * @file Explosion.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief 
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Explosion.h"
#include <iostream>

Explosion::Explosion() {
    stage = 9;
}

string Explosion::getName() const {
    return "Explosion";
}

int Explosion::getStage() const {
    return stage / 3;
}

void Explosion::decrementStage() {
    stage--;
}