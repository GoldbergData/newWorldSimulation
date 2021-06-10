//header

#ifndef _AlienBase_h
#define _AlienBase_h

#include <string>
using namespace std;

//VERY UNFINISHED, BARE MINIMUM FOR PLANET INSERT
class AlienBase {
private:
    string name;
    long population;
    int cooldown;
public:
    AlienBase();
    AlienBase(string name);
    virtual string getName() const;
    virtual long getPopulation() const;
    virtual long getIncrease() const;
    virtual int getCooldown() const;
    virtual void setPopulation(long newPopulation);
    virtual void reduceCooldown();
    virtual void resetCooldown();
};
#endif
