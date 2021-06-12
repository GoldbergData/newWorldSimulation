//header

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Galaxy.h"
#include "SpaceObject.h"
#include "Planet.h"
#include "Star.h"
#include "AlienBase.h"
#include "Zed.h"
#include "Explosion.h"
#include "ToxicWasteland.h"
#include "EventHandler.h"
#include "ClassFilter.h"
using namespace std;

Galaxy::Galaxy(int rows, int cols, string filename) {
    galaxy = generateEmptyGrid(rows, cols);
    spaceships = generateEmptyGrid(rows, cols);
    explosions = generateEmptyGrid(rows, cols);
    generateFromFile(filename);
}

vector<vector<SpaceObject*>>* Galaxy::generateEmptyGrid(int rows, int cols) {
    vector<vector<SpaceObject*>>* grid = new vector<vector<SpaceObject*>>;
    for (int i = 0; i < rows; i++) {
        vector<SpaceObject*> newRowSpaceObjects;
        grid->push_back(newRowSpaceObjects);
        for (int j = 0; j < cols; j++) {
            (*grid)[i].push_back(nullptr);
        }
    }
    return grid;
}

//separate if/else lists to methods
//update for aliens
void Galaxy::generateFromFile(string filename) {
    //grab bounds, set up
    ifstream read;
    read.open(filename);
    int spaceObjectCount; read >> spaceObjectCount;
    int alienCount; read >> alienCount;
    //read space object spawning data
    for (int i = 0; i < spaceObjectCount; i++) {
        string type; read >> type;
        string temp;
        read >> temp; int row = 0; row = stoi(temp);
        read >> temp; int col = 0; col = stoi(temp);
        read >> temp; int moveset = 0; moveset = stoi(temp);
        SpaceObject* spaceObject;
        initializeSpaceObject(type, &spaceObject, Movesets(moveset));
        (*galaxy)[row][col] = spaceObject;
    }
    //read alien spawning data
    for (int i = 0; i < alienCount; i++) {
        string type; read >> type;
        string temp;
        read >> temp; int row = 0; row = stoi(temp);
        read >> temp; int col = 0; col = stoi(temp);
        AlienBase* alienBase;
        initializeAlienBase(type, &alienBase);
        SpaceObject* spaceObject = (*galaxy)[row][col];
        ((Planet*)spaceObject)->setOccupant(alienBase);
    }
}

SpaceObject* Galaxy::getSpaceObject(int row, int col) const {
    return (*galaxy)[row][col];
}

AlienBase* Galaxy::getOccupant(int row, int col) const {
    SpaceObject* spaceObject = (*galaxy)[row][col];
    if (spaceObject->isHabitable()) {
        return ((Planet*)spaceObject)->getOccupant();
    }
    return nullptr;
}

SpaceObject* Galaxy::getSpaceship(int row, int col) const {
     return (*spaceships)[row][col];
}

SpaceObject* Galaxy::getExplosion(int row, int col) const {
     return (*explosions)[row][col];
}

int Galaxy::getSize() const {
    return galaxy->size();
}

void Galaxy::update(long turn) {
    int size = galaxy->size();
    vector<vector<SpaceObject*>>* newGalaxy = generateEmptyGrid(size, size);
    vector<vector<SpaceObject*>>* newSpaceships = generateEmptyGrid(size, size);
    vector<vector<SpaceObject*>>* newExplosions = generateEmptyGrid(size, size);
    for (int i = 0; i < galaxy->size(); i++) {
        for (int j = 0; j < galaxy->size(); j++) {
            //move planets
            SpaceObject* spaceObject = (*galaxy)[i][j];
            SpaceObject* spaceship = (*spaceships)[i][j];
            SpaceObject* explosion = (*explosions)[i][j];
            if (spaceObject != nullptr) {
                updateSpaceObject(turn, i, j, spaceObject, newGalaxy, newSpaceships);
            }
            if (spaceship != nullptr) {
                if (spaceObject != nullptr) {
                    interactSpaceObject(spaceObject, spaceship);
                }
                updateShip(turn, i, j, spaceship, newGalaxy, newSpaceships,
                        newExplosions);
            }
            if (explosion != nullptr) {
                (*newExplosions)[i][j] = explosion;
            }
        }
    }
    galaxy = newGalaxy;
    spaceships = newSpaceships;
    explosions = newExplosions;
}

void Galaxy::updateSpaceObject(long turn, int row, int col, SpaceObject* spaceObject,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips) {
    //move planets
    Movesets moveset = spaceObject->getMoveset();
    Moves move = getMove(turn, moveset);
    updateCoordinates(row, col, move, galaxy->size());
    (*newGalaxy)[row][col] = spaceObject;
    //update population counts
    if (spaceObject->isHabitable()) {
        AlienBase* occupant = ((Planet*)spaceObject)->getOccupant();
        if (occupant != nullptr) {
            bool full = updatePopulation(spaceObject, occupant);
            if (full && occupant->getCooldown() == 0) {
                sendShip(occupant, &(*newShips)[row][col]);
            }
        }
    }
}

void Galaxy::updateShip(long turn, int row, int col, SpaceObject* spaceShip,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips,
            vector<vector<SpaceObject*>>* newExplosions) {
    Movesets moveset = spaceShip->getMoveset();
    Moves move = getMove(turn, moveset);
    int oldRow = row;
    int oldCol = col;
    //changes coordinates to where the ship wants to move
    updateCoordinates(row, col, move, galaxy->size());
    //space is empty, move ship to new space
    if ((*newShips)[row][col] == nullptr) {
        (*newShips)[row][col] = spaceShip;
        ((Spaceship*)spaceShip)->setLastMove(move);
        //check for planet at new location and update interactions if one exists
        SpaceObject* spaceObject = (*newGalaxy)[row][col];
        if(spaceObject != nullptr) {
            int winner = interactSpaceObject(spaceObject, spaceShip);
            if (winner == 1) {
                SpaceObject* newExplosion = new Explosion();
                (*newExplosions)[oldRow][oldCol] = newExplosion;
            } else if (winner == 2) {
                string alienType = ((Spaceship*)spaceShip)->getOccupant()->getName();
                AlienBase* newOccupant;
                initializeAlienBase(alienType, &newOccupant);
                ((Planet*)spaceObject)->setOccupant(newOccupant);
            }
        }
    //space is not empty, update board according to interact results
    } else {
        SpaceObject* otherShip = (*newShips)[row][col];
        int winner = interactShips(spaceShip, otherShip);
        SpaceObject* newExplosion = new Explosion();        //free memory?
        if (winner == 1) {
            (*newShips)[oldRow][oldCol] = spaceShip;
            (*newExplosions)[row][col] = newExplosion;
        } else if (winner == 2) {
            (*newExplosions)[oldRow][oldCol] = newExplosion;
            (*newShips)[row][col] = otherShip;
        }
    }
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
    temp += ("(" + spaceObject->getName());
    if (spaceObject->isHabitable()) {;
        temp += (":" + ((Planet*)spaceObject)->getOccupant()->getName() + ")");
        if (!fencepost) {
            temp += ", ";
        }
    } else {
        temp += ")";
    }
    return temp;
}