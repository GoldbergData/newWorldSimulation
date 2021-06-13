/**
 * @file IceWorld.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Bare planet class. Did not have time to implement differences.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _IceWorld_h
#define _IceWorld_h

#include "Planet.h"
#include <string>

class IceWorld : public Planet {
private:
public:
    IceWorld(Movesets moveset);
    virtual int getHazard() const;
    virtual string getName() const;
};

#endif