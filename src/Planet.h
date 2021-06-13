/**
 * @file Planet.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief A habitable SpaceObject.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Planet_h
#define _Planet_h

#include "SpaceObject.h"
#include "AlienBase.h"
#include "Orbits.h"

//header
class Planet : public SpaceObject {
private:
    AlienBase* occupant;
    long capacity;
    // Currently not used.
    int baseTemperature;
public:
    /**
     * @brief Construct a new Planet object.
     * 
     * @param moveset Orbital path.
     */
    Planet(Movesets moveset);

    /**
     * @brief Get the population capacity of the planet.
     * 
     * @return long Population capacity.
     */
    long getCapacity() const;

    /**
     * @brief Get the Temperature object. Currently not used.
     * 
     * @return int Temperature.
     */
    int getTemperature() const;

    /**
     * @brief Determines if a planet is habitable, which is always true.
     * 
     * @return true Habitable.
     */
    virtual bool isHabitable() const;

    /**
     * @brief Set the alien occupants of the planet.
     * 
     * @param occupant Alien.
     */
    void setOccupant(AlienBase* occupant);

    /**
     * @brief Get the alien occupants of the planet.
     * 
     * @return AlienBase* Alien.
     */
    AlienBase* getOccupant() const;

    /**
     * @brief Get the hazard of the planet, which reduces population growth of
     * the occupants on the planet.
     * 
     * @return int Hazard.
     */
    virtual int getHazard() const;

    /**
     * @brief Get the bonus of the planet, which increases population growth of
     * the occupants on the planet.
     * 
     * @return int Bonus.
     */    
    virtual int getBonus() const;

    /**
     * @brief Get the name of the class.
     * 
     * @return string Name of the class.
     */
    virtual string getName() const;
};

#endif