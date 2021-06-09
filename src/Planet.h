//header

#ifndef _Planet_h
#define _Planet_h

#include "SpaceObject.h"
#include "AlienBase.h"
#include "Orbits.h"

//header
class Planet : public SpaceObject {
private:
    AlienBase* occupant;
    long capacity;
    int baseTemperature;
public:
    Planet(string color, long capacity, int baseTemperature, Movesets moveset);
    long getCapacity() const;
    int getTemperature() const;
    virtual bool isHabitable() const;
    void setOccupant(AlienBase* occupant);
    AlienBase* getOccupant() const;
    virtual int getHazard() const;
    virtual int getBonus() const;
};

#endif