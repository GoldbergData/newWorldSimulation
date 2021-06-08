//header

#ifndef _Galaxy_h
#define _Galaxy_h

#include <string>
#include <vector>
#include "SpaceObject.h"
#include "AlienBase.h"
using namespace std;

class Galaxy {
    friend ostream& operator <<(ostream& out, const Galaxy& list);
private:
    vector<vector<SpaceObject*>>* galaxy;
    //add a moveset to the SpaceObjects as well.
    //string filename; to read in our hand-made galaxy from file
    //int turns; to track movement of the planets, will probably have to 
public:
    Galaxy(int rows, int cols/*filename*/);
    SpaceObject* getSpaceObject(int row, int col) const;
    AlienBase* getOccupant(int row, int col) const;
    void setSpaceObject(int row, int col, SpaceObject* object);
    void setOccupant(int row, int col, AlienBase* occupant);
    int getSize() const;
};
string printHelper(SpaceObject* spaceObject, bool fencepost);


#endif