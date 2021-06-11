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
    vector<vector<SpaceObject*>>* explosions;
public:
    Galaxy(int rows, int cols, string filename);
    vector<vector<SpaceObject*>>* generateEmptyGrid(int rows, int cols);
    void generateGalaxyFile(string filename);
    SpaceObject* getSpaceObject(int row, int col) const;
    AlienBase* getOccupant(int row, int col) const;
    SpaceObject* getSpaceship(int row, int col) const;
    SpaceObject* getExplosion(int row, int col) const;
    void setSpaceObject(int row, int col, SpaceObject* object);
    void setOccupant(int row, int col, AlienBase* occupant);   //mark
    void setSpaceship(int row, int col, SpaceObject* spaceship);
    int getSize() const;
    void update(long currentTurn);
    void spawnShip(int row, int col, AlienBase* occupant,
            vector<vector<SpaceObject*>>* newSpaceships);
    void updateMovesSpaceObject(long turn, int row, int col, SpaceObject* objectToMove,
            vector<vector<SpaceObject*>>* newGalaxy);
    void updateMovesShip(long turn, int row, int col, SpaceObject* objectToMove,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips,
            vector<vector<SpaceObject*>>* newExplosions);
    AlienBase* createColony(string alienType);
    void updateCoordinates(int& row, int& col, Moves move);
    bool updatePopulation(SpaceObject* spaceObject, AlienBase* occupant);
    void moveSpaceObject(long turn, int row, int col, SpaceObject* spaceObject,
            vector<vector<SpaceObject*>>* newGalaxy);
    int interactShips(SpaceObject* ship1, SpaceObject* ship2);
    int interactSpaceObject(SpaceObject* spaceObject, SpaceObject* ship);
};
string printHelper(SpaceObject* spaceObject, bool fencepost);


#endif