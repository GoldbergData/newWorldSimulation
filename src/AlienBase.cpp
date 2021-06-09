//header

#include "AlienBase.h"
#include <string>
using namespace std;

AlienBase::AlienBase() {
    name = "AlienBase";
    population = 10000;
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

void AlienBase::setPopulation(long newPopulation) {
    population = newPopulation;
}