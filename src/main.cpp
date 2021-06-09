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
    testGUI.generateGalaxyFile("TestGalaxy.txt");
    testGUI.redraw();
    for (int i = 0; i < 100; i++) {
        testGUI.update();
    }
    return 0;
}