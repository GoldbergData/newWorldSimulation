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
    int getCapacity();
    int getTemperature();
    bool isHabitable() override;
    void setOccupant(AlienBase* occupant);
    virtual int getHazard();
    virtual int getBonus();
};

#endif
