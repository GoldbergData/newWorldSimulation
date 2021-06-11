//header

#ifndef _SpaceObject_h
#define _SpaceObject_h

#include <string>
#include "Orbits.h"
using namespace std;

//After beta phase color can probably become an image
class SpaceObject {
private:
    Movesets moveset;
public:
    SpaceObject();
    SpaceObject(Movesets moveset);
    virtual bool isHabitable() const;
    Movesets getMoveset() const;
    virtual string getName() const;
};

#endif