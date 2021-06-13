/**
 * @file Orbits.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Utility enums and vectors used for handling object movements.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _Orbits_h
#define _Orbits_h

#include <vector>
using namespace std;

enum Movesets{STATIONARY, CLOSE, MEDIUM, RANDOM, CLOSECC, MEDIUMSLOW, FAR};
enum Moves{CENTER, NORTH, EAST, SOUTH, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST};
const vector<Moves> circle = {SOUTH, WEST, NORTH, EAST};
const vector<Moves> circleCC = {WEST, SOUTH, EAST, NORTH};

//CURRENT INITIAL SPOTS FOR ALL ORBITS - TOP RIGHT CORNER, CLOCKWISE
/**
 * @brief Get the move direction.
 * @pre Planets are placed in the top right corner of their orbits.
 * 
 * @param currentTurn Current iteration in the simulation.
 * @param moveSet Characterizes orbit path.
 * @return Moves Direction.
 */
Moves getMove(long currentTurn, Movesets moveSet);

/**
 * @brief Updates the coordinates based on the specified move.
 * 
 * @param rows Vertical positioning in the simulation window.
 * @param cols Horizontal positioning in the simulation window.
 * @param move Direction.
 * @param gridSize Size of grid to handle off-mapping (when an object moves
 * past the boundaries, it appears on the other side of the grid).
 */
void updateCoordinates(int& row, int& col, Moves move, int gridSize);

#endif