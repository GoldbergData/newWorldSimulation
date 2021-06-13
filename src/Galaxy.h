/**
 * @file Galaxy.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief A Galaxy is used to store all grid objects required for the simulation.
 * Additionally, Galaxy handles all the computation for updating objects'
 * positions in the grid and interaction between other objects on encounters. All
 * stored objects in the grid will be initialized as nullptrs, which result in
 * an empty space when drawing the simulation. A requirement for all galaxies is
 * a predefined map.txt file. Two are provided to show examples (see Map1.txt,
 * Map2.txt).
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Galaxy_h
#define _Galaxy_h

#include <string>
#include <vector>
#include "SpaceObject.h"
#include "AlienBase.h"
#include "Spaceship.h"
using namespace std;

class Galaxy {
    /**
     * @brief Helper printer method used to print the grid of objects.
     * 
     * @param out 
     * @param list 
     * @return ostream& 
     */
    friend ostream& operator <<(ostream& out, const Galaxy& list);
private:
    // Grids used for displaying content. Spaceship and explosion were made into
    // seperate grids so they do not take up space in the galaxy (i.e, spacehships
    // and explosions can occur over objects inside the galaxy grid).
    vector<vector<SpaceObject*>>* galaxy;
    vector<vector<SpaceObject*>>* spaceships;
    vector<vector<SpaceObject*>>* explosions;
public:
    /**
     * @brief Construct a new Galaxy object. Generate three empty grids for
     * members galaxy, spaceships, and explosions.
     * 
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @param filename Uses a predefined map file to populate the grids' default
     * values.
     */
    Galaxy(int rows, int cols, string filename);

    /**
     * @brief Generic method to create an empty grid.
     * 
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @return vector<vector<SpaceObject*>>* A grid.
     */
    vector<vector<SpaceObject*>>* generateEmptyGrid(int rows, int cols);

    /**
     * @brief A predefined map file used to populate the grids with objects.
     * 
     * @param filename A map file name ending in .txt.
     */
    void generateFromFile(string filename);

    /**
     * @brief Get the SpaceObject object.
     * 
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @return SpaceObject* SpaceObject at the location in the grid.
     */
    SpaceObject* getSpaceObject(int row, int col) const;

    /**
     * @brief Get the alien (occupant) of a planet from the galaxy grid.
     * 
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @return AlienBase* AlienBase at the location in the grid. 
     */
    AlienBase* getOccupant(int row, int col) const;

    /**
     * @brief Get the spaceship object from the spaceship grid.
     * 
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @return SpaceObject* SpaceObject (spaceship) at the location in the grid. 
     */
    SpaceObject* getSpaceship(int row, int col) const;

    /**
     * @brief Get the explosion object from the spaceship grid.
     * 
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @return SpaceObject* SpaceObject (explosion) at the location in the grid.
     */
    SpaceObject* getExplosion(int row, int col) const;

    /**
     * @brief Get the Size object. Number of rows and columns in the grid.
     * @pre Assumes the grid is a square.
     * 
     * @return int 
     */
    int getSize() const;

    /**
     * @brief Updates the state of all grids. New grids are generated each turn
     * of the iteration and replace the old grids.
     * 
     * @param turn One iteration of the simulation.
     */
    void update(long turn);

    /**
     * @brief Updates the population count, SpaceObject positions, and spawns
     * spaceships.
     * 
     * @param turn The current iteration of the simulation.
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @param spaceObject A single SpaceObject in the galaxy grid.
     * @param newGalaxy A new galaxy grid used for repositioning.
     * @param newShips A new spaceship grid used for repositioning.
     */
    void updateSpaceObject(long turn, int row, int col, SpaceObject* spaceObject,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips);

    /**
     * @brief Decides spaceship actions (moving and interaction with other SpaceObjects).
     * @param turn The current iteration of the simulation.
     * @param rows Max number of rows (y, i.e height) in the grid.
     * @param cols Max number of cols (x, i.e width) in the grid.
     * @param spaceShip A single spaceship in the spaceship grid.
     * @param newGalaxy A new galaxy grid used for repositioning.
     * @param newShips A new spaceship grid used for repositioning.
     * @param newExplosions A new explosion grid used for repositioning.
     */
    void updateShip(long turn, int row, int col, SpaceObject* spaceShip,
            vector<vector<SpaceObject*>>* newGalaxy, vector<vector<SpaceObject*>>* newShips,
            vector<vector<SpaceObject*>>* newExplosions);
};

/**
 * @brief Print helper for printing out a grid.
 * 
 * @param spaceObject A SpaceObject.
 * @param fencepost A bool specifying whether the print is a fencepost.
 * @return string A printed output.
 */
string printHelper(SpaceObject* spaceObject, bool fencepost);


#endif