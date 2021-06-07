//header
#include <iostream>
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

// overrides the print (<<) operator for std vectors that contain any type
// prints them out surrounded by curly brackets {} with a comma and a space
// between each pair of numbers.
ostream& operator <<(ostream& out, const Galaxy& list) {
    if (list.galaxy->size() == 0) {
        out << "{{}}";
    } else {
        out << "{" << endl;
        int lastOuter = list.galaxy->size() - 1;
        for (int i = 0; i < list.galaxy->size() - 1; i++) {
            if ((*list.galaxy)[i].size() == 0) {
                out << "{}";
            } else {
                int lastInner = (*list.galaxy)[i].size() - 1;
                out << "\t" << "{";
                for(int j = 0; j < list.galaxy->size() - 1; j++) {
                    if (j % 4 == 0 && j != 0) {
                        out << endl << "\t";
                    }
                    SpaceObject* val = (*list.galaxy)[i][j];
                    out << printHelper(val, false);
                }
                SpaceObject* val = (*list.galaxy)[i][lastInner];
                out << printHelper(val, true);
                out << "}," << endl << endl;
            }

        }
        //fencepost
        out << "\t{";
        for(int j = 0; j < lastOuter; j++) {
            if (j % 4 == 0 && j != 0) {
                out << endl << "\t";
            }
            SpaceObject* val = (*list.galaxy)[lastOuter][j];
            out << printHelper(val, false);
        }
        int lastInner = (*list.galaxy)[lastOuter].size() - 1;
        SpaceObject* val = (*list.galaxy)[lastOuter][lastInner];
        out << printHelper(val, true);
        out << "}" << endl << "}";
    }
    return out;
}

string printHelper(SpaceObject* spaceObject, bool fencepost) {
    string temp = "";
    temp += ("(" + spaceObject->toString());
    if (spaceObject->isHabitable()) {;
        temp += (":" + ((Planet*)spaceObject)->getOccupant()->toString() + ")");
        if (!fencepost) {
            temp += ", ";
        }
    } else {
        temp += ")";
    }
    return temp;
}