//header

#ifndef _Explosion_h
#define _Explosion_h

#include "SpaceObject.h"
#include <string>

class Explosion : public SpaceObject {
private:
    int stage;
public:
    Explosion();
    virtual string getName() const;
    int getStage() const;
    void decrementStage();
};

#endif