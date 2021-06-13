/**
 * @file main.cpp
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief Runs the galaxy simulation.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>
#include "Galaxy.h"
#include "GalaxyGUI.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
    new GalaxyGUI(800, 40);
    return 0;
}