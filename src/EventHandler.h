#ifndef _EventHandler_h
#define _EventHandler_h

#include <string>
#include <vector>
#include "SpaceObject.h"
#include "AlienBase.h"
#include "Spaceship.h"
#include "Planet.h"

int interactSpaceObject(SpaceObject* spaceObject, SpaceObject* ship);
int interactShips(SpaceObject* ship1, SpaceObject* ship2);
bool updatePopulation(SpaceObject* spaceObject, AlienBase* occupant);
void sendShip(AlienBase* occupant, SpaceObject** spaceship);

#endif