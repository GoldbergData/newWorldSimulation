//header

#ifndef _SpaceObject_h
#define _SpaceObject_h

#include <string>
using namespace std;

//After beta phase color can probably become an image
class SpaceObject {
private:
    string color;
public:
    SpaceObject();
    SpaceObject(string color);
    virtual bool isHabitable() const;
    string getColor() const;
};

#endif
