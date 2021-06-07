//header

#include <string>
#include <vector>
#include "Galaxy.h"
#include "SpaceObject.h"
#include "Planet.h"
#include "AlienBase.h"
using namespace std;

//VERY TEMPORARY CONSTRUCTOR
Galaxy::Galaxy(/*filename*/) {
    //start with basic loop all same type of object, then file read later
    galaxy = new vector<vector<SpaceObject*>>;
    SpaceObject* object = new Planet("brown", 0, 0); //CHANGE SOON
    AlienBase* alien = new AlienBase();
    ((Planet*)object)->setOccupant(alien);
    for (int i = 0; i < 10; i++) { //CHANGE SOON
        vector<SpaceObject*> row;
        galaxy->push_back(row);
        for (int j = 0; j < 10; j++) {
            (*galaxy)[i].push_back(object);
        }
    }
}

SpaceObject* Galaxy::getSpaceObject(int row, int col) const {
    return (*galaxy)[row][col];
}

AlienBase* Galaxy::getOccupant(int row, int col) const {
    SpaceObject* object = (*galaxy)[row][col];
    if (object->isHabitable()) {
        return ((Planet*)object)->getOccupant();
    }
    return nullptr; //CHANGE LATER
}

void Galaxy::setObject(int row, int col, SpaceObject* object) {
    (*galaxy)[row][col] = object;
}

void Galaxy::setOccupant(int row, int col, AlienBase* occupant) {
    SpaceObject* object = (*galaxy)[row][col];
    if (object->isHabitable()) {
        ((Planet*)object)->setOccupant(occupant);
    }
}

int Galaxy::getSize() const {
    return 10; //or 15 or 20 for better resolution planets later
}