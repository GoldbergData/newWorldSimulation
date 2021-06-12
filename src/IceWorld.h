//header

#ifndef _IceWorld_h
#define _IceWorld_h

#include "Planet.h"
#include <string>

class IceWorld : public Planet {
private:
public:
    IceWorld(Movesets moveset);
    virtual int getHazard() const;
    virtual string getName() const;
};

#endif