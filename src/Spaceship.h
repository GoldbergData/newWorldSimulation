//header

#ifndef _Spaceship_h
#define _Spaceship_h

#include <string>
#include "Orbits.h"
using namespace std;

class Spaceship {
private:
    string name;
    Moves move;
public:
    Spaceship(string name);
    string getName() const;
    Moves getMove() const;
};

#endif