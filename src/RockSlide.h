//header

#ifndef _RockSlide_h
#define _RockSlide_h

#include "Planet.h"
#include <string>

class RockSlide : public Planet {
private:
public:
    RockSlide(Movesets moveset);
    virtual int getHazard() const;
    virtual string getName() const;
};

#endif