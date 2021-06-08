#include <vector>
#include "Galaxy.h"
#include "GalaxyGUI.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
    //Galaxy galaxy(30, 30);
    //cout << galaxy << endl;
    GalaxyGUI testGUI(600, 30);
    testGUI.generateTestGalaxy();
    testGUI.redraw();
    return 0;
}