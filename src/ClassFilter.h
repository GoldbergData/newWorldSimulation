/**
 * @file ClassFilter.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Utility functions for creating new instances of aliens and space objects.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _ClassFilter_h
#define _ClassFilter_h

#include <string>
#include "SpaceObject.h"
#include "AlienBase.h"
using namespace std;

/**
 * @brief Creates a SpaceObject with a given type and moveset.
 * 
 * @param type Type is a string fetched from
 * getName() member method, which represents the class of the SpaceObject passed
 * to this method.
 * @param spaceObject A pointer to a SpaceObject* to initialize.
 * @param moveset A predetermined orbit path defined by an enum Movesets. Options
 * include: {STATIONARY, CLOSE, MEDIUM, RANDOM, CLOSECC, MEDIUMSLOW, FAR}.
 */
void initializeSpaceObject(string type, SpaceObject** spaceObject, Movesets moveset);

/**
 * @brief Creates a AlienBase with a given type.
 * 
 * @param type Type is a string fetched from
 * getName() member method, which represents the class of the AlienBase passed
 * to this method.
 * @param spaceObject A pointer to a AlienBase* to initialize.
 */
void initializeAlienBase(string type, AlienBase** alienBase);

#endif