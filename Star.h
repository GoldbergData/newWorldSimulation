//header

#ifndef _Star_h
#define _Star_h

#include <string>
#include "SpaceObject.h"
using namespace std;

class Star : public SpaceObject {
private:
    int temperature;
public:
    Star();
    int getTemperature() const;
};

#endif
