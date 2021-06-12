//header

#ifndef _Greenhouse_h
#define _Greenhouse_h

#include "Planet.h"
#include <string>

class Greenhouse : public Planet {
private:
public:
    Greenhouse(Movesets moveset);
    virtual int getHazard() const;
    virtual string getName() const;
};

#endif