/**
 * @file Spaceship.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief A spaceship is used when the population of a planet reaches its max
 * capacity. The primary purpose is to occupy other planets through exploration of
 * the galaxy.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Spaceship_h
#define _Spaceship_h

#include <string>
#include "Orbits.h"
#include "SpaceObject.h"
#include "AlienBase.h"
using namespace std;

class Spaceship : public SpaceObject {
private:
    AlienBase* occupant;
    Moves lastMove;
public:
    /**
     * @brief Construct a new Spaceship object.
     * 
     */
    Spaceship(AlienBase*);
    
    /**
     * @brief Get the occupant of the spaceship.
     * 
     * @return AlienBase* Alien.
     */
    AlienBase* getOccupant() const;

    /**
     * @brief Get the last move of the spaceship.
     * 
     * @return Moves Direction.
     */
    Moves getLastMove() const;

    /**
     * @brief Set the last move of the spaceship.
     * 
     * @param move Direction.
     */
    void setLastMove(Moves move);
};

#endif