#include "ClassFilter.h"
#include "Orbits.h"

#include "Planet.h"
#include "Star.h"
#include "ToxicWasteland.h"

#include "Zed.h"

void initializeSpaceObject(string type, SpaceObject** spaceObject, Movesets moveset) {
    if (type == "Star") {
        *spaceObject = new Star();
    } else if (type == "Planet") {
        *spaceObject = new Planet(moveset);
    } else if (type == "ToxicWasteland") {
        *spaceObject = new ToxicWasteland(moveset);
    } else {
        *spaceObject = nullptr;
    }
}

void initializeAlienBase(string type, AlienBase** alienBase) {
    if (type == "AlienBase") {
        *alienBase = new AlienBase();
    } else if (type == "Zed") {
        *alienBase = new Zed();
    }else {
        *alienBase = nullptr;
    }
}