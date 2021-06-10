//header
#ifndef _Orbits_h
#define _Orbits_h

#include <vector>
using namespace std;

enum Movesets{STATIONARY, CLOSE, MEDIUM, RANDOM};
enum Moves{CENTER, NORTH, EAST, SOUTH, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST};
const vector<Moves> circle = {SOUTH, WEST, NORTH, EAST};
//const vector<Moves> circle = {WEST, SOUTH, EAST, NORTH};

//CURRENT INITIAL SPOTS FOR ALL ORBITS - TOP RIGHT CORNER, CLOCKWISE
Moves getMove(long currentTurn, Movesets moveSet);

#endif