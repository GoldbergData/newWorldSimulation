/**
 * @file Orbits.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief 
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Orbits.h"
#include <iostream>
using namespace std;

Moves getMove(long currentTurn, Movesets moveSet) {
    if (moveSet == STATIONARY) {
        return CENTER;
    } else if (moveSet == CLOSE) {
        return circle[currentTurn / 2 % circle.size()];
    } else if (moveSet == MEDIUM) {
        return circle[currentTurn / 4 % circle.size()];
    } else if (moveSet == RANDOM) {
        return circle[rand() % circle.size()];
    } else if (moveSet == CLOSECC) {
        return circleCC[currentTurn / 2 % circle.size()];
    } else if (moveSet == MEDIUMSLOW) {
        return (currentTurn % 2 == 0) ? CENTER : (circle[currentTurn / 8 % circle.size()]);
    } else if (moveSet == FAR) {
        return circle[currentTurn / 6 % circle.size()];
    }else {
        return CENTER;
    }
}

void updateCoordinates(int& row, int& col, Moves move, int gridSize) {
    if (move == NORTH) {
        row -= 1;
    } else if (move == NORTHEAST) {
        row -= 1;
        col += 1;
    } else if (move == EAST) {
        col += 1;
    } else if (move == SOUTHEAST) {
        row += 1;
        col += 1;
    } else if (move == SOUTH) {
        row += 1;
    } else if (move == SOUTHWEST) {
        row += 1;
        col += 1;
    } else if (move == WEST) {
        col -= 1;
    } else if (move == NORTHWEST) {
        row -= 1;
        col -= 1;
    }
    //handle edge wrapping of coordinates
    if (row == gridSize) {
        row = 0;
    } else if (row < 0) {
        row = gridSize - 1;
    }
    if (col == gridSize) {
        col = 0;
    } else if (col < 0) {
        col = gridSize - 1;
    }
}