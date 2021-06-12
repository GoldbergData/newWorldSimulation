//header
#ifndef _Orbits_h
#define _Orbits_h

#include <vector>
using namespace std;

enum Movesets{STATIONARY, CLOSE, MEDIUM, RANDOM, CLOSECC, MEDIUMSLOW, FAR};
enum Moves{CENTER, NORTH, EAST, SOUTH, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST};
const vector<Moves> circle = {SOUTH, WEST, NORTH, EAST};
const vector<Moves> circleCC = {WEST, SOUTH, EAST, NORTH};

//CURRENT INITIAL SPOTS FOR ALL ORBITS - TOP RIGHT CORNER, CLOCKWISE
Moves getMove(long currentTurn, Movesets moveSet);
void updateCoordinates(int& row, int& col, Moves move, int gridSize);

#endif