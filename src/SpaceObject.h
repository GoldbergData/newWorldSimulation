/**
 * @file SpaceObject.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief A superclass used for objects in the grids of Galaxy class.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SpaceObject_h
#define _SpaceObject_h

#include <string>
#include "Orbits.h"
using namespace std;

class SpaceObject {
private:
    Movesets moveset;
public:
    /**
     * @brief Construct a new Space Object object.
     * 
     */
    SpaceObject();

    /**
     * @brief Construct a new Space Object object
     * 
     * @param moveset Orbital path.
     */
    SpaceObject(Movesets moveset);

    /**
     * @brief If a SpaceObject is habitable. Not habitable (false) by default.
     * 
     * @return true Habitable.
     * @return false Not habitable.
     */
    virtual bool isHabitable() const;

    /**
     * @brief Get the Moveset, which is the orbital path of a SpaceObject.
     * 
     * @return Movesets 
     */
    Movesets getMoveset() const;

    /**
     * @brief Get the class name.
     * 
     * @return string class name.
     */
    virtual string getName() const;
};

#endif