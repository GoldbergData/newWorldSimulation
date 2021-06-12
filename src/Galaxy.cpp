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
using namespace std;

//VERY TEMPORARY CONSTRUCTOR
Galaxy::Galaxy(int rows, int cols, string filename) {
    galaxy = generateEmptyGrid(rows, cols);
    spaceships = generateEmptyGrid(rows, cols);
    explosions = generateEmptyGrid(rows, cols);
    generateGalaxyFile(filename);
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
void Galaxy::generateGalaxyFile(string filename) {
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
        if (type == "Star") {
            spaceObject = new Star();
        } else if (type == "Planet") {
            spaceObject = new Planet(Movesets(moveset));
        } else if (type == "ToxicWasteland") {
            spaceObject = new ToxicWasteland(Movesets(moveset));
        } else {
            spaceObject = nullptr;
        }
        (*galaxy)[row][col] = spaceObject;
    }
    //read alien spawning data
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

SpaceObject* Galaxy::getExplosion(int row, int col) const {
     return (*explosions)[row][col];
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
                updateMovesShip(currentTurn, i, j, spaceship, newGalaxy, newSpaceships,
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

//interact file?
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
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips,
            vector<vector<SpaceObject*>>* newExplosions) {
    Movesets moveset = objectToMove->getMoveset();
    Moves move = getMove(turn, moveset);
    //Changes coordinates to where the ship wants to move
    updateCoordinates(row, col, move);
    //Moves ship to new location if empty.
    int oldRow = row;
    int oldCol = col;
    if ((*newShips)[row][col] == nullptr) {
        (*newShips)[row][col] = objectToMove;
        ((Spaceship*)objectToMove)->setLastMove(move);
        //Checks for planet at new location and interacts if one exists
        SpaceObject* spaceObject = (*newGalaxy)[row][col];
        if(spaceObject != nullptr) {
            int winner = interactSpaceObject(spaceObject, objectToMove);
            if (winner == 1) {
                SpaceObject* newExplosion = new Explosion();
                (*newExplosions)[oldRow][oldCol] = newExplosion;
            } else if (winner == 2) {
                string alienType = ((Spaceship*)objectToMove)->getOccupant()->getName();
                AlienBase* newOccupant = createColony(alienType);
                ((Planet*)spaceObject)->setOccupant(newOccupant);
            }
        }
    //Interacts with other ship if space is not empty
    } else {
        SpaceObject* otherObject = (*newShips)[row][col];
        int winner = interactShips(objectToMove, otherObject);
        SpaceObject* newExplosion = new Explosion();        //free memory?
        if (winner == 1) {
            (*newShips)[oldRow][oldCol] = objectToMove;
            (*newExplosions)[row][col] = newExplosion;
        } else if (winner == 2) {
            (*newExplosions)[oldRow][oldCol] = newExplosion;
            (*newShips)[row][col] = otherObject;
        }
    }
}

//interact file?
AlienBase* Galaxy::createColony(string alienType) {
    AlienBase* newColony;
    if (alienType == "Zed") {
        newColony = new Zed();
    } else {
        newColony = new AlienBase();
    }
    return newColony;
}

//move to orbits?
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
    //handle edge wrapping of coordinates
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

//interact file?
//0 = no fight, 1 = ship1 wins, 2 = ship2 wins
int Galaxy::interactShips(SpaceObject* ship1, SpaceObject* ship2) {
    //Checks if occupants belong to different factions
    string occupant1 = ((Spaceship*)ship1)->getOccupant()->getName();
    string occupant2 = ((Spaceship*)ship2)->getOccupant()->getName();
    if (occupant1 != occupant2) { 
        //Determine winner of the fight if different factions
        long pop1 = ((Spaceship*)ship1)->getOccupant()->getPopulation();
        long pop2 = ((Spaceship*)ship2)->getOccupant()->getPopulation();
        if (pop1 == pop2) {
            int winner = rand() % 2;
            if (winner) {
                return 2;
            } else {
                return 1;
            }
        } else if (pop1 > pop2) {
            return 1;
        } else {
            return 2;
        }
    }
    return 0;
}

//interact file?
//0 if no action, 1 if ship destroyed, 2 if colonize
int Galaxy::interactSpaceObject(SpaceObject* spaceObject, SpaceObject* ship) {
    //Check for planet
    if (spaceObject->isHabitable()) {
        AlienBase* occupant = ((Planet*)spaceObject)->getOccupant();
        string shipOccupant = ((Spaceship*)ship)->getOccupant()->getName();
        //Check if planet is inhabited
        if (occupant != nullptr) {
            string planetOccupant = occupant->getName();
            //Check if not friendly
            if (planetOccupant != shipOccupant) { 
                long popPlanet = occupant->getPopulation() / 3;
                long popShip = ((Spaceship*)ship)->getOccupant()->getPopulation();
                double ratio = (double) popPlanet / popShip;
                if (ratio > .95 || ratio < 1.05) {
                    int winner = rand() % 2;
                    return winner ? 1 : 2;
                }
            }
        //If planet is not inhabited
        } else {
            return 2;
        }
        
    }
    return 0;
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