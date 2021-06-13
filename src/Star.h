/**
 * @file Star.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief A star has planets that orbit around it. Stars are not habitable and
 * spaceships can fly past them without damage.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Star_h
#define _Star_h

#include <string>
#include "SpaceObject.h"
using namespace std;

class Star : public SpaceObject {
private:
    // Currently not used
    int temperature;
    /**
     * @brief Image used to represent the star.
     * 
     */
    string filename;
public:
    /**
     * @brief Construct a new Star object using a random star image.
     * 
     */
    Star();

    /**
     * @brief Get the Temperature object.
     * 
     * @return int 
     */
    int getTemperature() const;

    /**
     * @brief Get the name of the object.
     * 
     * @return string 
     */
    virtual string getName() const;

    /**
     * @brief Get the Filename of the object, which is used as the star's image.
     * 
     * @return string Name of image file for the star.
     */
    virtual string getFilename() const;
};

#endif