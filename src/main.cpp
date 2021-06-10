#include <vector>
#include "Galaxy.h"
#include "GalaxyGUI.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
    //Galaxy galaxy(30, 30);
    //cout << galaxy << endl;
    GalaxyGUI testGUI(800, 40);
    testGUI.redraw();
    //testGUI.generateTestGalaxy();
    for (int i = 0; i < 500; i++) {
        testGUI.redraw();
    }
    return 0;
}