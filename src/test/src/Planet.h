//header

#ifndef _Planet_h
#define _Planet_h

#include "SpaceObject.h"
#include "AlienBase.h"

//header
class Planet : public SpaceObject {
private:
    AlienBase* occupant;
    int capacity;
    int baseTemperature;
public:
    Planet(string color, int capacity, int baseTemperature);
    int getCapacity() const;
    int getTemperature() const;
    virtual bool isHabitable() const;
    void setOccupant(AlienBase* occupant);
    AlienBase* getOccupant() const;
    virtual int getHazard() const;
    virtual int getBonus() const;
};

#endif