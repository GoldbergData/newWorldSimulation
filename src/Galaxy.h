//header

#ifndef _Galaxy_h
#define _Galaxy_h

#include <string>
#include <vector>
#include "SpaceObject.h"
#include "AlienBase.h"
using namespace std;

class Galaxy {
private:
    vector<vector<SpaceObject*>>* galaxy;
    //add a moveset to the SpaceObjects as well.
    //string filename; to read in our hand-made galaxy from file
    //int turns; to track movement of the planets, will probably have to 
public:
    Galaxy(/*filename*/);
    SpaceObject* getSpaceObject(int row, int col) const;
    AlienBase* getOccupant(int row, int col) const;
    void setObject(int row, int col, SpaceObject* object);
    void setOccupant(int row, int col, AlienBase* occupant);
    int getSize() const;
};

#endif