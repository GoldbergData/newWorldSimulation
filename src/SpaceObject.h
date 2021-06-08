//header

#ifndef _SpaceObject_h
#define _SpaceObject_h

#include <string>
#include "Orbits.h"
using namespace std;

//After beta phase color can probably become an image
class SpaceObject {
private:
    string color;
    Movesets moveSet;
public:
    SpaceObject();
    SpaceObject(string color, Movesets moveSet);
    virtual bool isHabitable() const;
    string getColor() const;
    string toString() const;
};

#endif