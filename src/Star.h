//header

#ifndef _Star_h
#define _Star_h

#include <string>
#include "SpaceObject.h"
using namespace std;

class Star : public SpaceObject {
private:
    int temperature;
    string filename;
public:
    Star();
    int getTemperature() const;
    virtual string getName() const;
    virtual string getFilename() const;
};

#endif