//header

#ifndef _Explosion_h
#define _Explosion_h

#include "SpaceObject.h"
#include <string>

class Explosion : public SpaceObject {
private:
    string image;
public:
    Explosion();
    virtual string getName() const;
    void setImage(string filename);
};

#endif