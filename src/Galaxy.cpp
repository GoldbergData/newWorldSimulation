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
using namespace std;

//VERY TEMPORARY CONSTRUCTOR
Galaxy::Galaxy(int rows, int cols, string filename) {
    galaxy = generateEmptyGalaxy(rows, cols);
    spaceships = generateEmptyShips(rows, cols);
    generateGalaxyFile(filename);
}

vector<vector<SpaceObject*>>* Galaxy::generateEmptyGalaxy(int rows, int cols) {
    vector<vector<SpaceObject*>>* galaxy = new vector<vector<SpaceObject*>>;
    for (int i = 0; i < rows; i++) {
        vector<SpaceObject*> newRowSpaceObjects;
        galaxy->push_back(newRowSpaceObjects);
        for (int j = 0; j < cols; j++) {
            (*galaxy)[i].push_back(nullptr);
        }
    }
    return galaxy;
}

vector<vector<Spaceship*>>* Galaxy::generateEmptyShips(int rows, int cols) {
    vector<vector<Spaceship*>>* spaceships = new vector<vector<Spaceship*>>;
    for (int i = 0; i < rows; i++) {
        vector<Spaceship*> newRowShips;
        spaceships->push_back(newRowShips);
        for (int j = 0; j < cols; j++) {
            (*spaceships)[i].push_back(nullptr);
        }
    }
    return spaceships;
}

//update for aliens
void Galaxy::generateGalaxyFile(string filename) {
    ifstream read;
    read.open(filename);
    int spaceObjectCount; read >> spaceObjectCount;
    int alienCount; read >> alienCount;
    for (int i = 0; i < spaceObjectCount; i++) {
        string type; read >> type;
        string color; read >> color;
        string temp;
        read >> temp; int row = 0; row = stoi(temp);
        read >> temp; int col = 0; col = stoi(temp);
        read >> temp; int moveset = 0; moveset = stoi(temp);
        SpaceObject* spaceObject;
        if (type == "Star") {
            spaceObject = new Star();
        } else if (type == "Planet") {
            spaceObject = new Planet(color, 1000000, 0, Movesets(moveset));
        } else {
            spaceObject = nullptr;
        }
        (*galaxy)[row][col] = spaceObject;
    }
    for (int i = 0; i < alienCount; i++) {
        string alienType; read >> alienType;
        string temp;
        read >> temp; int row = 0; row = stoi(temp);
        read >> temp; int col = 0; col = stoi(temp);
        AlienBase* alienBase;
        if (alienType == "AlienBase") {
            alienBase = new AlienBase();
        }
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
    return nullptr; //CHANGE LATER
}

Spaceship* Galaxy::getSpaceship(int row, int col) const {
     return (*spaceships)[row][col];
}

void Galaxy::setSpaceObject(int row, int col, SpaceObject* spaceObject) {
    (*galaxy)[row][col] = spaceObject;
}

void Galaxy::setOccupant(int row, int col, AlienBase* occupant) {
    SpaceObject* spaceObject = (*galaxy)[row][col];
    if (spaceObject->isHabitable()) {
        ((Planet*)spaceObject)->setOccupant(occupant);
    }
}

void Galaxy::setSpaceship(int row, int col, Spaceship* spaceship) {
    (*spaceships)[row][col] = spaceship;
}

int Galaxy::getSize() const {
    return galaxy->size();
}

void Galaxy::update(long currentTurn) {
    int tiles = galaxy->size();
    vector<vector<SpaceObject*>>* newGalaxy = generateEmptyGalaxy(tiles, tiles);
    vector<vector<Spaceship*>>* newSpaceships = generateEmptyShips(tiles, tiles);
    for (int i = 0; i < galaxy->size(); i++) {
        for (int j = 0; j < galaxy->size(); j++) {
            //move planets
            SpaceObject* spaceObject = (*galaxy)[i][j];
            Spaceship* spaceship = (*spaceships)[i][j];
            if (spaceObject != nullptr) {
                moveSpaceObject(currentTurn, i, j, spaceObject, newGalaxy);
                //update population counts
                if (spaceObject->isHabitable()) {
                    AlienBase* occupant = ((Planet*)spaceObject)->getOccupant();
                    if (occupant != nullptr) {
                        bool full = updatePopulation(spaceObject, occupant);
                        if (full) {
                            spawnShip(i, j, occupant, newSpaceships);
                        }
                    }
                }
            }
            if (spaceship != nullptr) {
                //moveSpaceship
                (*newSpaceships)[i][j] = spaceship;
            }
        }
    }
    galaxy = newGalaxy;
    spaceships = newSpaceships;
}

void Galaxy::spawnShip(int row, int col, AlienBase* occupant,
            vector<vector<Spaceship*>>* newSpaceships) {
    Spaceship* newShip = new Spaceship(occupant->getName());
    (*newSpaceships)[row][col] = newShip;
}

void Galaxy::moveShips() {

}

bool Galaxy::updatePopulation(SpaceObject* spaceObject, AlienBase* occupant) {
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
    //cout << newPopulation << endl; //
    return full;
}

void Galaxy::moveSpaceObject(long turn, int row, int col, SpaceObject* spaceObject,
            vector<vector<SpaceObject*>>* newGalaxy) {
    Movesets moveset = spaceObject->getMoveset();
    Moves move = getMove(turn, moveset);
    if (move == NORTH) {
        (*newGalaxy)[row - 1][col] = spaceObject;
    } else if (move == NORTHEAST) {
        (*newGalaxy)[row - 1][col + 1] = spaceObject;
    } else if (move == EAST) {
        (*newGalaxy)[row][col + 1] = spaceObject;
    } else if (move == SOUTHEAST) {
        (*newGalaxy)[row + 1][col + 1] = spaceObject;
    } else if (move == SOUTH) {
        (*newGalaxy)[row + 1][col] = spaceObject;
    } else if (move == SOUTHWEST) {
        (*newGalaxy)[row + 1][col - 1] = spaceObject;
    } else if (move == WEST) {
        (*newGalaxy)[row][col - 1] = spaceObject;
    } else if (move == NORTHWEST) {
        (*newGalaxy)[row - 1][col - 1] = spaceObject;
    } else {
        (*newGalaxy)[row][col] = spaceObject;
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
    temp += ("(" + spaceObject->toString());
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