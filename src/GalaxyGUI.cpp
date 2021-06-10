//header
#include <string>
#include <vector>
#include "GalaxyGUI.h"
#include "console.h"
#include "Star.h"
#include "Planet.h"
#include "Orbits.h"
#include "Galaxy.h"
#include "SpaceObject.h"
#include "Spaceship.h"


#include <ctime>
#include <ratio>
#include <chrono>
using namespace std::chrono;

using namespace sgl;
using namespace std;

GalaxyGUI::GalaxyGUI(int windowSize, int squareSize) {
    window = new GWindow();
    window->setCanvasSize(windowSize, windowSize);
    window->setLocation(300, 100);
    //window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    int tileCount = windowSize / squareSize;
    galaxy = new Galaxy(tileCount, tileCount, "TestGalaxy.txt");
    this->windowSize = windowSize;
    this->squareSize = squareSize;
    currentTurn = 0;
}

void GalaxyGUI::update() {
    galaxy->update(currentTurn);
}

void GalaxyGUI::redraw() {
    update();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    currentTurn++;
    window->clearCanvasPixels();
    for (int i = 0; i < galaxy->getSize(); i++) {
        for (int j = 0; j < galaxy->getSize(); j++) {
            SpaceObject* spaceObject = galaxy->getSpaceObject(i, j);
            Spaceship* spaceship = galaxy->getSpaceship(i, j);
            if (spaceObject != nullptr) {
                string color = "";
                color = galaxy->getSpaceObject(i, j)->getColor();
                window->setColor(color);
                window->fillOval(j * squareSize, i * squareSize, squareSize, squareSize); // x = col, y = row
                AlienBase* occupant = galaxy->getOccupant(i, j);
                if (occupant != nullptr) {
                    string name = galaxy->getOccupant(i, j)->getName();
                    window->setColor("white");
                    window->drawString(name.substr(0 , 1), j * squareSize, i * squareSize); // x = col, y = row
                }
            }
            //super temp test
            if (spaceship != nullptr) {
                window->setColor("red");
                int smaller = squareSize / 3;
                window->fillRect(j * squareSize, i * squareSize, smaller, smaller); // x = col, y = row
            }
        }
    }
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    window->repaint();
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    /*duration<double> time1 = t2 - t1;
    duration<double> time2 = t3 - t2;
    duration<double> time3 = t4 - t3;
    cout << "Update: " << time1.count() << endl;
    cout << "Process and print: " << time2.count() << endl;
    cout << "Repaint: " << time3.count() << endl;*/
}



