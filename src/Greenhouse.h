/**
 * @file Greenhouse.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Bare planet class. Did not have time to implement differences.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Greenhouse_h
#define _Greenhouse_h

#include "Planet.h"
#include <string>

class Greenhouse : public Planet {
private:
public:
    Greenhouse(Movesets moveset);
    virtual int getHazard() const;
    virtual string getName() const;
};

#endif