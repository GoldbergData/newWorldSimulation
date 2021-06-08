//header
#ifndef _Orbits_h
#define _Orbits_h

#include <vector>
using namespace std;

enum Movesets{STATIONARY, CLOSE, MEDIUM};
enum Moves{CENTER, NORTH, EAST, SOUTH, WEST};
const vector<Moves> circle = {SOUTH, WEST, NORTH, EAST};
//Moves getMove(int currentTurn, Movesets moveSet);

//CURRENT INITIAL SPOTS FOR ALL ORBITS - TOP RIGHT CORNER, CLOCKWISE
Moves getOrbit(int currentTurn, Movesets moveSet);

#endif