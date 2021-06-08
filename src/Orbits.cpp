#include "Orbits.h"

Moves getOrbit(int currentTurn, Movesets moveSet) {
    if (moveSet == STATIONARY) {
        return CENTER;
    } else if (moveSet == CLOSE) {
        return circle[currentTurn / 2 % circle.size()];
    } else if (moveSet == MEDIUM) {
        return circle[currentTurn / 4 % circle.size()];
    } else {
        return CENTER;
    }
}