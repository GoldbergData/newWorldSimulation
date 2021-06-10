#include "Orbits.h"
#include <iostream>
using namespace std;

Moves getMove(long currentTurn, Movesets moveSet /*int offset*/) {
    //currentTurn += offset; //to start somewhere other than top right corner
    if (moveSet == STATIONARY) {
        return CENTER;
    } else if (moveSet == CLOSE) {
        return circle[currentTurn / 2 % circle.size()];
    } else if (moveSet == MEDIUM) {
        return circle[currentTurn / 4 % circle.size()];
    } else if (moveSet == RANDOM) {
        return circle[rand() % circle.size()];
    } else {
        return CENTER;
    }
}