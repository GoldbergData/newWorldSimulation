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
public:
    AlienBase();
    string getName() const;
    long getPopulation() const;
    long getIncrease() const;
    void setPopulation(long newPopulation);

};
#endif
