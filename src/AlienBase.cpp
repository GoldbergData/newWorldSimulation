/**
 * @file AlienBase.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "AlienBase.h"
#include <string>
using namespace std;

AlienBase::AlienBase() {
    name = "AlienBase";
    population = 10000;
    cooldown = 0;
}

AlienBase::AlienBase(string name) {
    this->name = name;
    population = 10000;
    cooldown = 0;
}

string AlienBase::getName() const {
    return name;
}

long AlienBase::getPopulation() const {
    return population;
}

long AlienBase::getIncrease() const {
    return population / 10;
}

int AlienBase::getCooldown() const {
    return cooldown;
}

void AlienBase::setPopulation(long newPopulation) {
    population = newPopulation;
}

void AlienBase::reduceCooldown() {
    if (cooldown != 0) {
        cooldown--;
    }
}

void AlienBase::resetCooldown() {
    cooldown = 75;
}