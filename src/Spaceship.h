//header

#ifndef _Spaceship_h
#define _Spaceship_h

#include <string>
#include "Orbits.h"
#include "SpaceObject.h"
#include "AlienBase.h"
using namespace std;

class Spaceship : public SpaceObject {
private:
    AlienBase* occupant;
    Moves lastMove;
public:
    Spaceship(AlienBase*);
    AlienBase* getOccupant() const;
    Moves getLastMove() const;
    void setLastMove(Moves move);
};

#endif