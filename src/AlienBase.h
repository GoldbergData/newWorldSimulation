/**
 * @file AlienBase.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Superclass for all alien types. AlienBase has a default population
 * of 10,000 and a increase of 10% for every iteration of the simulation. 
 * AlienBase occupies either a Planet or Spaceship.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _AlienBase_h
#define _AlienBase_h

#include <string>
using namespace std;

class AlienBase {
private:
    string name;
    long population;
    int cooldown;
public:
    /**
     * @brief Construct a new Alien Base object
     * 
     */

    AlienBase();
    /**
     * @brief Construct a new Alien Base object. Used for when subclasses have
     * different names than AlienBase.
     * 
     * @param name Primarily used for naming an Alien subclass.
     */

    AlienBase(string name);
    /**
     * @brief Get the Name object. This is used to fetch the type of Alien 
     * subclass, which allows to instantiate different aliens on planets and
     * spaceships. Additionally, the name of the Alien is used for alien
     * spaceship file names (ex. PinkGoblinN.png).
     * 
     * @return string Name of class.
     */

    virtual string getName() const;
    /**
     * @brief Get the Population object. Population is used to calculate the
     * growth of the planet population for each interation of the simulation. 
     * 
     * @return long Population.
     */

    virtual long getPopulation() const;
    /**
     * @brief Get the Increase object
     * 
     * @return long 
     */

    /**
     * @brief Get the Increase object, which determines population growth. 
     * 
     * @return long Population increase.
     */
    virtual long getIncrease() const;

    /**
     * @brief Get the Cooldown object, which determines the cool-down period for
     * spawning new spaceships.
     * 
     * @return int 
     */
    virtual int getCooldown() const;

    /**
     * @brief Set the Population object.
     * 
     * @param newPopulation 
     */
    virtual void setPopulation(long newPopulation);

    /**
     * @brief Reduces cool-down for spawning a new ship by 1. Does not reduce
     * if cool-down is zero.
     * 
     */
    virtual void reduceCooldown();

    /**
     * @brief Resets cool-down for spawning a spaceship. Reset value defaults to
     * 75.
     * 
     */
    virtual void resetCooldown();
};
#endif
