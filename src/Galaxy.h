//header

#ifndef _Galaxy_h
#define _Galaxy_h

#include <string>
#include <vector>
#include "SpaceObject.h"
#include "AlienBase.h"
#include "Spaceship.h"
using namespace std;

class Galaxy {
    friend ostream& operator <<(ostream& out, const Galaxy& list);
private:
    vector<vector<SpaceObject*>>* galaxy;
    vector<vector<SpaceObject*>>* spaceships;
public:
    Galaxy(int rows, int cols, string filename);
    vector<vector<SpaceObject*>>* generateEmptyGalaxy(int rows, int cols);
    vector<vector<SpaceObject*>>* generateEmptyShips(int rows, int cols);
    void generateGalaxyFile(string filename);
    SpaceObject* getSpaceObject(int row, int col) const;
    AlienBase* getOccupant(int row, int col) const;
    SpaceObject* getSpaceship(int row, int col) const;
    void setSpaceObject(int row, int col, SpaceObject* object);
    void setOccupant(int row, int col, AlienBase* occupant);
    void setSpaceship(int row, int col, SpaceObject* spaceship);
    int getSize() const;
    void update(long currentTurn);
    void spawnShip(int row, int col, AlienBase* occupant,
            vector<vector<SpaceObject*>>* newSpaceships);
    void updateMovesSpaceObject(long turn, int row, int col, SpaceObject* objectToMove,
            vector<vector<SpaceObject*>>* newGalaxy);
    void updateMovesShip(long turn, int row, int col, SpaceObject* objectToMove,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips);
    void updateCoordinates(int& row, int& col, Moves move);
    bool updatePopulation(SpaceObject* spaceObject, AlienBase* occupant);
    void moveSpaceObject(long turn, int row, int col, SpaceObject* spaceObject,
            vector<vector<SpaceObject*>>* newGalaxy);
    void interactShips(SpaceObject* ship1, SpaceObject* ship2);
    void interactSpaceObject(SpaceObject* spaceObject, SpaceObject* ship);
};
string printHelper(SpaceObject* spaceObject, bool fencepost);


#endif