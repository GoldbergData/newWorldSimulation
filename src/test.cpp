//Testing code

#include "SpaceObject.h"
#include "Star.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    //Star constructor test, just checking if syntax worked
    Star sun = Star();
    cout << "Color: " << sun.getColor() << endl;
    cout << "Temperature: " << sun.getTemperature() << endl;
    return 0;
}
