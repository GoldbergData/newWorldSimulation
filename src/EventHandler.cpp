#include "EventHandler.h"
#include "ClassFilter.h"
#include <iostream>

int interactSpaceObject(SpaceObject* spaceObject, SpaceObject* ship) {
    //check for planet
    if (spaceObject->isHabitable()) {
        AlienBase* occupant = ((Planet*)spaceObject)->getOccupant();
        string shipOccupant = ((Spaceship*)ship)->getOccupant()->getName();
        //check if planet is inhabited
        if (occupant != nullptr) {
            string planetOccupant = occupant->getName();
            //check if not friendly
            if (planetOccupant != shipOccupant) { 
                long popPlanet = occupant->getPopulation() / 3;
                long popShip = ((Spaceship*)ship)->getOccupant()->getPopulation();
                double ratio = (double) popPlanet / popShip;
                if (ratio > .95 || ratio < 1.05) {
                    int winner = rand() % 2;
                    return winner ? 1 : 2;
                }
            }
        //if planet is not inhabited
        } else {
            return 2;
        }
        
    }
    return 0;
}

//0 = no fight, 1 = ship1 wins, 2 = ship2 wins
int interactShips(SpaceObject* ship1, SpaceObject* ship2) {
    //checks if occupants belong to different factions
    string occupant1 = ((Spaceship*)ship1)->getOccupant()->getName();
    string occupant2 = ((Spaceship*)ship2)->getOccupant()->getName();
    cout << occupant1 << ", " << occupant2 << endl;
    if (occupant1 != occupant2) { 
        //determine winner of the fight if different factions
        long pop1 = ((Spaceship*)ship1)->getOccupant()->getPopulation();
        long pop2 = ((Spaceship*)ship2)->getOccupant()->getPopulation();
        if (pop1 == pop2) {
            int winner = rand() % 2;
            if (winner) {
                return 2;
            } else {
                return 1;
            }
        } else if (pop1 > pop2) {
            return 1;
        } else {
            return 2;
        }
    }
    return 0;
}

//true if full planet
bool updatePopulation(SpaceObject* spaceObject, AlienBase* occupant) {
    bool full = false;
    long population = occupant->getPopulation();
    long populationCap = ((Planet*)spaceObject)->getCapacity();
    long baseIncrease = occupant->getIncrease();
    long bonus = ((Planet*)spaceObject)->getBonus();
    long hazard = ((Planet*)spaceObject)->getHazard();
    long finalChange = baseIncrease + bonus - hazard;
    long newPopulation = population + finalChange;
    if (newPopulation < 0) {
        newPopulation = 0;
    } else if (newPopulation >= populationCap) {
        newPopulation = populationCap;
        full = true;
    }
    occupant->setPopulation(newPopulation);
    occupant->reduceCooldown();
    return full;
}

void sendShip(AlienBase* occupant, SpaceObject** spaceship) {
    //generate ship and crew
    AlienBase* crew;
    string type = occupant->getName();
    initializeAlienBase(type, &crew);
    long crewPopulation = occupant->getPopulation() / 4;
    SpaceObject* newShip = new Spaceship(crew);
    //reduce planet poulation and start cooldown
    occupant->resetCooldown();
    long newPopulation = occupant->getPopulation() - crewPopulation;
    occupant->setPopulation(newPopulation);
    *spaceship = newShip;
}