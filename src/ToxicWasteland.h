//header

#ifndef _ToxicWasteland_h
#define _ToxicWasteland_h

#include "Planet.h"
#include <string>

class ToxicWasteland : public Planet {
private:
public:
    ToxicWasteland(Movesets moveset);
    virtual int getHazard() const;
    virtual string getName() const;
};

#endif