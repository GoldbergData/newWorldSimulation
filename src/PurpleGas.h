//header

#ifndef _PurpleGas_h
#define _PurpleGas_h

#include "Planet.h"
#include <string>

class PurpleGas : public Planet {
private:
public:
    PurpleGas(Movesets moveset);
    virtual int getHazard() const;
    virtual string getName() const;
};

#endif