#ifndef _ClassFilter_h
#define _ClassFilter_h

#include <string>
#include "SpaceObject.h"
#include "AlienBase.h"
using namespace std;

void initializeSpaceObject(string type, SpaceObject** spaceObject, Movesets moveset);
void initializeAlienBase(string type, AlienBase** alienBase);

#endif