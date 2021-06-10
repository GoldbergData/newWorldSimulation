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

vector<vector<SpaceObject*>>* Galaxy::generateEmptyShips(int rows, int cols) {
    vector<vector<SpaceObject*>>* spaceships = new vector<vector<SpaceObject*>>;
    for (int i = 0; i < rows; i++) {
        vector<SpaceObject*> newRowShips;
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
        } else if (alienType == "Zed") {
            alienBase = new Zed();
        }else {
            alienBase = nullptr;
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

SpaceObject* Galaxy::getSpaceship(int row, int col) const {
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

void Galaxy::setSpaceship(int row, int col, SpaceObject* spaceship) {
    (*spaceships)[row][col] = spaceship;
}

int Galaxy::getSize() const {
    return galaxy->size();
}

void Galaxy::update(long currentTurn) {
    int tiles = galaxy->size();
    vector<vector<SpaceObject*>>* newGalaxy = generateEmptyGalaxy(tiles, tiles);
    vector<vector<SpaceObject*>>* newSpaceships = generateEmptyShips(tiles, tiles);
    for (int i = 0; i < galaxy->size(); i++) {
        for (int j = 0; j < galaxy->size(); j++) {
            //move planets
            SpaceObject* spaceObject = (*galaxy)[i][j];
            SpaceObject* spaceship = (*spaceships)[i][j];
            if (spaceObject != nullptr) {
                updateMovesSpaceObject(currentTurn, i, j, spaceObject, newGalaxy);
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
                if (spaceObject != nullptr) {
                    interactSpaceObject(spaceObject, spaceship);
                }
                updateMovesShip(currentTurn, i, j, spaceship, newGalaxy, newSpaceships);
            }
        }
    }
    galaxy = newGalaxy;
    spaceships = newSpaceships;
}

void Galaxy::spawnShip(int row, int col, AlienBase* occupant,
            vector<vector<SpaceObject*>>* newSpaceships) {
    if (occupant->getCooldown() == 0) {
        string alienType = occupant->getName();
        AlienBase* colony;
        if (alienType == "Zed") {
            colony = new Zed();
        } else {
            colony = new AlienBase();
        }
        long colonyPopulation = occupant->getPopulation() / 4;
        SpaceObject* newShip = new Spaceship(colony);
        (*newSpaceships)[row][col] = newShip;
        occupant->resetCooldown();
        //reduce planet poulation
        long newPopulation = occupant->getPopulation() - colonyPopulation;
        occupant->setPopulation(newPopulation);

    }
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
    occupant->reduceCooldown();
    return full;
}

void Galaxy::updateMovesSpaceObject(long turn, int row, int col, SpaceObject* objectToMove,
            vector<vector<SpaceObject*>>* newGalaxy) {
    Movesets moveset = objectToMove->getMoveset();
    Moves move = getMove(turn, moveset);
    updateCoordinates(row, col, move);
    (*newGalaxy)[row][col] = objectToMove;
}

void Galaxy::updateMovesShip(long turn, int row, int col, SpaceObject* objectToMove,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips) {
    Movesets moveset = objectToMove->getMoveset();
    Moves move = getMove(turn, moveset);
    updateCoordinates(row, col, move);
    if ((*newShips)[row][col] == nullptr) {
        (*newShips)[row][col] = objectToMove;
        ((Spaceship*)objectToMove)->setLastMove(move);
        SpaceObject* spaceObject = (*newGalaxy)[row][col];
        if(spaceObject != nullptr) {
            interactSpaceObject(spaceObject, objectToMove);
        }
    } else {
        SpaceObject* otherObject = (*newShips)[row][col];
        interactShips(objectToMove, otherObject);
    }
}

void Galaxy::updateCoordinates(int& row, int& col, Moves move) {
    if (move == NORTH) {
        row -= 1;
    } else if (move == NORTHEAST) {
        row -= 1;
        col += 1;
    } else if (move == EAST) {
        col += 1;
    } else if (move == SOUTHEAST) {
        row += 1;
        col += 1;
    } else if (move == SOUTH) {
        row += 1;
    } else if (move == SOUTHWEST) {
        row += 1;
        col += 1;
    } else if (move == WEST) {
        col -= 1;
    } else if (move == NORTHWEST) {
        row -= 1;
        col -= 1;
    }
    if (row == galaxy->size()) {
        row = 0;
    } else if (row < 0) {
        row = galaxy->size() - 1;
    }
    if (col == galaxy->size()) {
        col = 0;
    } else if (col < 0) {
        col = galaxy->size() - 1;
    }
}

void Galaxy::interactShips(SpaceObject* ship1, SpaceObject* ship2) {
    string occupant1 = ((Spaceship*)ship1)->getOccupant()->getName();
    string occupant2 = ((Spaceship*)ship2)->getOccupant()->getName();
    if (occupant1 != occupant2) { 
        long pop1 = ((Spaceship*)ship1)->getOccupant()->getPopulation();
        long pop2 = ((Spaceship*)ship2)->getOccupant()->getPopulation();
        if (pop1 == pop2) {
            int winner = rand() % 2;
            winner ? ship1 = nullptr : ship2 = nullptr;
        } else if (pop1 > pop2) {
            ship2 = nullptr;
        } else {
            ship1 = nullptr;
        }
    }
}

void Galaxy::interactSpaceObject(SpaceObject* spaceObject, SpaceObject* ship) {
    if (spaceObject->isHabitable()) {
        AlienBase* occupant = ((Planet*)spaceObject)->getOccupant();
        string shipOccupant = ((Spaceship*)ship)->getOccupant()->getName();
        if (occupant != nullptr) {
            string planetOccupant = occupant->getName();
            if (planetOccupant != shipOccupant) { 
                long popPlanet = occupant->getPopulation() / 3;
                long popShip = ((Spaceship*)ship)->getOccupant()->getPopulation();
                double ratio = (double) popPlanet / popShip;
                if (ratio > .95 || ratio < 1.05) {
                    int winner = rand() % 2;
                    if (winner) {
                        ship = nullptr;
                    } else {
                        AlienBase* colonizers;
                        if (shipOccupant == "AlienBase") {
                            colonizers = new AlienBase();
                        } else if (shipOccupant == "Zed") {
                            colonizers = new Zed();
                        }
                        occupant = colonizers;
                        ship = nullptr;
                    } 
                }
            }
        } else {
            AlienBase* colonizers;
            if (shipOccupant == "AlienBase") {
                colonizers = new AlienBase();
            } else if (shipOccupant == "Zed") {
                colonizers = new Zed();
            }
            occupant = colonizers;
            ship = nullptr;
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