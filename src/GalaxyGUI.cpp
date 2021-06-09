//header
#include <fstream>
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

using namespace sgl;

GalaxyGUI::GalaxyGUI(int windowSize, int squareSize) {
    window = new GWindow();
    window->setCanvasSize(windowSize, windowSize);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    galaxy = new Galaxy(windowSize / squareSize, windowSize / squareSize);
    this->windowSize = windowSize;
    this->squareSize = squareSize;
    currentTurn = 0;
}

void GalaxyGUI::update() {
    Galaxy* newGalaxy = new Galaxy(windowSize / squareSize, windowSize / squareSize);
    for (int i = 0; i < galaxy->getSize(); i++) {
        for (int j = 0; j < galaxy->getSize(); j++) {
            //move planets
            SpaceObject* spaceObject = galaxy->getSpaceObject(i, j);
            Spaceship* spaceship = galaxy->getSpaceship(i, j);
            if (spaceObject != nullptr) {
                moveSpaceObject(i, j, spaceObject, newGalaxy);
                //update population counts
                if (spaceObject->isHabitable()) {
                    AlienBase* occupant = ((Planet*)spaceObject)->getOccupant();
                    if (occupant != nullptr) {
                        bool full = updatePopulation(spaceObject, occupant);
                        if (full) {
                            //spawnShip(i, j, occupant, newGalaxy);
                            Spaceship* newShip = new Spaceship(occupant->getName());
                            newGalaxy->setSpaceship(i, j, newShip);
                        }
                    }
                }
            }
            if (spaceship != nullptr) {
                //moveSpaceship
                newGalaxy->setSpaceship(i, j, spaceship);
            }
        }
    }
    galaxy = newGalaxy;
    currentTurn++;
    redraw();
}

void GalaxyGUI::spawnShip(int row, int col, AlienBase* occupant, Galaxy* galaxy) {
    Spaceship* newShip = new Spaceship(occupant->getName());
    galaxy->setSpaceship(row, col, newShip);
}

void GalaxyGUI::moveShips() {

}

bool GalaxyGUI::updatePopulation(SpaceObject* spaceObject, AlienBase* occupant) {
    bool full = false;
    long population = occupant->getPopulation();
    long populationCap = ((Planet*)spaceObject)->getCapacity();
    long baseIncrease = occupant->getIncrease();
    long bonus = ((Planet*)spaceObject)->getBonus();
    long hazard = ((Planet*)spaceObject)->getHazard();
    long finalChange = baseIncrease + bonus - hazard;
    long newPopulation = population + finalChange;
    if (newPopulation < 0) {
        newPopulation = 0;
    } else if (newPopulation >= populationCap) {
        newPopulation = populationCap;
        full = true;
    }
    occupant->setPopulation(newPopulation);
    cout << newPopulation << endl; //
    return full;
}

void GalaxyGUI::moveSpaceObject(int row, int col, SpaceObject* spaceObject, Galaxy* newGalaxy) {
    Movesets moveset = spaceObject->getMoveset();
    Moves move = getMove(currentTurn, moveset);
    if (move == NORTH) {
        newGalaxy->setSpaceObject(row - 1, col, spaceObject);
    } else if (move == NORTHEAST) {
        newGalaxy->setSpaceObject(row - 1, col + 1, spaceObject);
    } else if (move == EAST) {
        newGalaxy->setSpaceObject(row, col + 1, spaceObject);
    } else if (move == SOUTHEAST) {
        newGalaxy->setSpaceObject(row + 1, col + 1, spaceObject);
    } else if (move == SOUTH) {
        newGalaxy->setSpaceObject(row + 1, col, spaceObject);
    } else if (move == SOUTHWEST) {
        newGalaxy->setSpaceObject(row + 1, col - 1, spaceObject);
    } else if (move == WEST) {
        newGalaxy->setSpaceObject(row, col - 1, spaceObject);
    } else if (move == NORTHWEST) {
        newGalaxy->setSpaceObject(row - 1, col - 1, spaceObject);
    } else {
        newGalaxy->setSpaceObject(row, col, spaceObject);
    }
}

void GalaxyGUI::redraw() {
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
                    string occupantString = galaxy->getOccupant(i, j)->getName();
                    window->setColor("white");
                    window->drawString(occupantString.substr(0 , 1), j * squareSize, i * squareSize); // x = col, y = row
                }
            }
            //super temp test
            if (spaceship != nullptr) {
                window->setColor("red");
                window->fillRect(j * squareSize, i * squareSize, squareSize / 3, squareSize / 3); // x = col, y = row
            }
        }
    }
    window->repaint();
}

//update for aliens
void GalaxyGUI::generateGalaxyFile(string filename) {
    ifstream read;
    read.open(filename);
    int spaceObjectCount;
    read >> spaceObjectCount;
    int alienCount;
    read >> alienCount;
    for (int i = 0; i < spaceObjectCount; i++) {
        string type;
        read >> type;
        string color;
        string temp;
        read >> color;
        read >> temp;
        int row = 0;
        row = stoi(temp);
        read >> temp;
        int col = 0;
        col = stoi(temp);
        read >> temp;
        int moveset = 0;
        moveset = stoi(temp);
        SpaceObject* spaceObject;
        if (type == "Star") {
            spaceObject = new Star();
        } else if (type == "Planet") {
            spaceObject = new Planet(color, 1000000, 0, Movesets(moveset));
        } else {
            spaceObject = nullptr;
        }
        galaxy->setSpaceObject(row, col, spaceObject);
    }
    for (int i = 0; i < alienCount; i++) {
        string alienType;
        string temp;
        read >> alienType;
        int row = 0;
        read >> temp;
        row = stoi(temp);
        int col = 0;
        read >> temp;
        col = stoi(temp);
        AlienBase* alienBase;
        if (alienType == "AlienBase") {
            alienBase = new AlienBase();
        }
        SpaceObject* spaceObject = galaxy->getSpaceObject(row, col);
        ((Planet*)spaceObject)->setOccupant(alienBase);
    }
}

