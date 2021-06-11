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
#include "Explosion.h"

using namespace sgl;

GalaxyGUI::GalaxyGUI(int windowSize, int squareSize) {
    window = new GWindow();
    window->setCanvasSize(windowSize, windowSize);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    int tileCount = windowSize / squareSize;
    galaxy = new Galaxy(tileCount, tileCount, "TestGalaxy.txt");
    this->windowSize = windowSize;
    this->squareSize = squareSize;
    currentTurn = 0;
    window->setTimerListener(300, [this] {
        // note that we use this lamdba function (basically an anonymous function) 
        // so that we can call our member function. We can call a non-member function 
        // by just listing the name as we did in our first version. However, that
        // doesn't work with member functions
        this->redraw();
    });
}



void GalaxyGUI::redraw() {
    galaxy->update(currentTurn);
    currentTurn++;
    window->clearCanvasPixels();
    window->drawImage("Background2.png", 0, 0);
    //Get coordinates
    for (int i = 0; i < galaxy->getSize(); i++) {
        for (int j = 0; j < galaxy->getSize(); j++) {
            //Grab SpaceObject and Spaceship
            SpaceObject* spaceObject = galaxy->getSpaceObject(i, j);
            SpaceObject* spaceship = galaxy->getSpaceship(i, j);
            SpaceObject* explosion = galaxy->getExplosion(i, j);
            //Draw SpaceObject if one exists
            if (spaceObject != nullptr) {
                //Grab object type as string to check
                string type = spaceObject->getName();
                if (type == "Star") {
                    string filename = ((Star*)spaceObject)->getFilename();
                    window->drawImage(filename, j * squareSize, i * squareSize);
                } else {
                    string filename = type + ".png";
                    window->drawImage(filename, j * squareSize + 5, i * squareSize + 5); 
                    AlienBase* occupant = galaxy->getOccupant(i, j);
                    if (occupant != nullptr) {
                        string name = galaxy->getOccupant(i, j)->getName();
                        window->setColor("white");
                        window->drawString(name.substr(0 , 1), j * squareSize, i * squareSize);
                    }
                }
            }
            //Draw Explosion if one exists
            if (explosion != nullptr) {
                int stage = ((Explosion*)explosion)->getStage();
                string name = ((Explosion*)explosion)->getName();
                if (stage > 0) {
                    string image = name + to_string(stage) + ".png";
                    ((Explosion*)explosion)->decrementStage();
                    window->drawImage(image, j * squareSize, i * squareSize);
                } else {
                    spaceObject = nullptr;
                }
            }
            //Draw Spaceship if one exists
            if (spaceship != nullptr) {
                string name = ((Spaceship*)spaceship)->getOccupant()->getName();
                Moves lastMove = ((Spaceship*)spaceship)->getLastMove();
                string imageFile = getImage(name, lastMove);
                window->drawImage(imageFile, j * squareSize + 5, i * squareSize + 5); // x = col, y = row
            }
            
        }
    }
    window->repaint();
}

string GalaxyGUI::getImage(string name, Moves lastMove) {
    return name + moveStrings[lastMove] + ".png";
}