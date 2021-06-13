/**
 * @file ClassFilter.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ClassFilter.h"
#include "Orbits.h"

#include "Planet.h"
#include "Star.h"
#include "ToxicWasteland.h"
#include "IceWorld.h"
#include "PurpleGas.h"
#include "RockSlide.h"
#include "Greenhouse.h"

#include "Zed.h"
#include "Patawlian.h"
#include "PinkGoblin.h"
#include "Saveela.h"

void initializeSpaceObject(string type, SpaceObject** spaceObject, Movesets moveset) {
    if (type == "Star") {
        *spaceObject = new Star();
    } else if (type == "Planet") {
        *spaceObject = new Planet(moveset);
    } else if (type == "ToxicWasteland") {
        *spaceObject = new ToxicWasteland(moveset);
    } else if (type == "IceWorld") {
        *spaceObject = new IceWorld(moveset);
    } else if (type == "PurpleGas") {
        *spaceObject = new PurpleGas(moveset);
    } else if (type == "RockSlide") {
        *spaceObject = new RockSlide(moveset);
    } else if (type == "Greenhouse") {
        *spaceObject = new Greenhouse(moveset);
    } else {
        *spaceObject = nullptr;
    }
}

void initializeAlienBase(string type, AlienBase** alienBase) {
    if (type == "AlienBase") {
        *alienBase = new AlienBase();
    } else if (type == "Zed") {
        *alienBase = new Zed();
    } else if (type == "Patawlian") {
        *alienBase = new Patawlian();
    } else if (type == "PinkGoblin") {
        *alienBase = new PinkGoblin();
    } else if (type == "Saveela") {
        *alienBase = new Saveela();                        
    } else {
        *alienBase = nullptr;
    }
}