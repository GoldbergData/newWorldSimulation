//heade
#include "GalaxyGUI.h"
#include "console.h"
#include "Star.h"
#include "Planet.h"

using namespace sgl;

GalaxyGUI::GalaxyGUI(int windowSize, int squareSize) {
    window = new GWindow();
    window->setCanvasHeight(windowSize);
    window->setCanvasWidth(windowSize);
    window->setBackground("black");
    window->setExitOnClose(true);
    galaxy = new Galaxy(windowSize / squareSize, windowSize / squareSize);
    this->windowSize = windowSize;
    this->squareSize = squareSize;
}

void GalaxyGUI::redraw() {
    window->clearCanvasPixels();
    for (int i = 0; i < galaxy->getSize(); i++) {
        for (int j = 0; j < galaxy->getSize(); j++) {
            SpaceObject* spaceObject = galaxy->getSpaceObject(i, j);
            if (spaceObject != nullptr) {
                string color = "";
                color = galaxy->getSpaceObject(i, j)->getColor();
                window->setColor(color);
                window->fillOval(i * squareSize, j * squareSize, squareSize, squareSize);
                AlienBase* occupant = galaxy->getOccupant(i, j);
                if (occupant != nullptr) {
                    string occupantString = galaxy->getOccupant(i, j)->toString();
                    window->setColor("white");
                    window->drawString(occupantString.substr(0 , 1), i * squareSize, j * squareSize);
                }
            }
        }
    }
}

void GalaxyGUI::generateTestGalaxy() {
    SpaceObject* star = new Star();
    galaxy->setSpaceObject(10, 10, star);
    SpaceObject* planet = new Planet("blue", 0, 0, CLOSE);
    galaxy->setSpaceObject(11, 9, planet);
}