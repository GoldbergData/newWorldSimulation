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
    void generateFromFile(string filename);
    SpaceObject* getSpaceObject(int row, int col) const;
    AlienBase* getOccupant(int row, int col) const;
    SpaceObject* getSpaceship(int row, int col) const;
    SpaceObject* getExplosion(int row, int col) const;
    int getSize() const;
    void update(long turn);
    void updateSpaceObject(long turn, int row, int col, SpaceObject* spaceObject,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips);
    void updateShip(long turn, int row, int col, SpaceObject* objectToMove,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips,
            vector<vector<SpaceObject*>>* newExplosions);
    void moveSpaceObject(long turn, int row, int col, SpaceObject* spaceObject,
            vector<vector<SpaceObject*>>* newGalaxy);
};
string printHelper(SpaceObject* spaceObject, bool fencepost);


#endif