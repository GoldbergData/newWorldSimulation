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
    vector<vector<Spaceship*>>* spaceships;
public:
    Galaxy(int rows, int cols);
    SpaceObject* getSpaceObject(int row, int col) const;
    AlienBase* getOccupant(int row, int col) const;
    Spaceship* getSpaceship(int row, int col) const;
    void setSpaceObject(int row, int col, SpaceObject* object);
    void setOccupant(int row, int col, AlienBase* occupant);
    void setSpaceship(int row, int col, Spaceship* spaceship);
    int getSize() const;
};
string printHelper(SpaceObject* spaceObject, bool fencepost);


#endif