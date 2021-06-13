/**
 * @file Explosion.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Explosions occur when a spaceship loses a battle (either by another
 * spaceship or by occupants of a planet).
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Explosion_h
#define _Explosion_h

#include "SpaceObject.h"
#include <string>

class Explosion : public SpaceObject {
private:
    int stage;
public:
    /**
     * @brief Construct a new Explosion object. Sets the stage to 9 (the biggest)
     * explosion size. As decrementStage() is called, the explosion size shrinks.
     * 
     */
    Explosion();

    /**
     * @brief Get the Name object.
     * 
     * @return string 
     */
    virtual string getName() const;

    /**
     * @brief Get the Stage object. A stage determines the size of the explosion.
     * 
     * @return int 
     */
    int getStage() const;

    /**
     * @brief Reduces the stage (size) of the explosion.
     * 
     */
    void decrementStage();
};

#endif