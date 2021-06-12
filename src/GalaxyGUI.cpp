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
#include "gthread.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gobjects.h"
#include "gtextfield.h"
using namespace sgl;

GRadioButton* grbBackground1;
GRadioButton* grbBackground2;
GRadioButton* grbBackground3;
GRadioButton* grbBackground4;
GButton* gbStart;
GButton* gbStop;

GalaxyGUI::GalaxyGUI(int windowSize, int squareSize) {
    //set GWindow
    window = new GWindow();
    window->setCanvasSize(windowSize + 100, windowSize);  //offset for buttons
    window->setLocation(300, 100);
    window->setBackground("black");   //background color for GUI buttons area
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    //initialize member variables
    int tileCount = windowSize / squareSize;
    galaxy = new Galaxy(tileCount, tileCount, "TestGalaxy.txt");
    this->windowSize = windowSize;
    this->squareSize = squareSize;
    backgroundImage = "Background2.png";
    currentTurn = 0;
    //creating buttons, other misc setup
    createButtons();
    createRadioButtons();
    redraw();
    window->setTimerListener(300, [this] {
        this->checkImage();
    });
}

void GalaxyGUI::checkImage() {
    if (grbBackground1->isSelected()) {
        setImage("Background2.png");
    } else {
        setImage("Background1.png");
    }
}

void GalaxyGUI::setImage(string imageFile) {
    backgroundImage = imageFile;
    redraw();
}

void GalaxyGUI::createButtons() {
    gbStart = new GButton("START");
    //gbTestButton1->setAccelerator("ctrl F");     // hotkey apparently
    gbStart->setClickListener([this] {
        //Timer listeners don't replace properly, and seem to perform the
        //actions of both listeners and using both time intervals. This
        //is a rough workaround.
        window->setTimerListener(999999, [this] {
            this->tick();
        });
    });
    gbStop = new GButton("STOP"); 
    gbStop->setClickListener([this] {
        //Remove doesnt remove, it seems to only pause.
        window->removeTimerListener();
        //Unpauses the checker for background image selection
        window->setTimerListener(999999, [this] {
            this->checkImage();
        });
    });
    window->addToRegion(gbStart, "East");
    window->addToRegion(gbStop, "East");
}

void GalaxyGUI::createSingleRadio(string text, GRadioButton** nameOut) {
    GRadioButton* button = new GRadioButton(text);
    button->setActionCommand(text);
    button->setColor("white");
    window->addToRegion(button, "East");
    *nameOut = button;
 }

void GalaxyGUI::createRadioButtons() {
    createSingleRadio("Dark Void", &grbBackground1);
    grbBackground1->setSelected(true);
    createSingleRadio("Blue Haze", &grbBackground2);
    createSingleRadio("unfinished", &grbBackground3);
    createSingleRadio("unfinished", &grbBackground4);
}

void GalaxyGUI::tick() {
    galaxy->update(currentTurn);
    currentTurn++;
    checkImage();
    redraw();
}

void GalaxyGUI::redraw() {
    window->clearCanvasPixels();
    window->drawImage(backgroundImage, 0, 0);
    //Get coordinates
    for (int i = 0; i < galaxy->getSize(); i++) {
        for (int j = 0; j < galaxy->getSize(); j++) {
            //Grab SpaceObject and Spaceship
            SpaceObject* spaceObject = galaxy->getSpaceObject(i, j);
            SpaceObject* spaceship = galaxy->getSpaceship(i, j);
            SpaceObject* explosion = galaxy->getExplosion(i, j);
            //Draw SpaceObject if one exists
            if (spaceObject != nullptr) {
                drawSpaceObject(spaceObject, i, j);
            }
            //Draw Spaceship if one exists
            if (spaceship != nullptr) {
                drawSpaceship(spaceship, i, j);
            }
            //Draw Explosion if one exists
            if (explosion != nullptr) {
                drawExplosion(explosion, i, j);
            }
        }
    }
    window->repaint();
}

void GalaxyGUI::drawSpaceObject(SpaceObject* spaceObject, int row, int col) {
    string type = spaceObject->getName();
    if (type == "Star") {
        string filename = ((Star*)spaceObject)->getFilename();
        window->drawImage(filename, col * squareSize, row * squareSize);
    } else {
        string filename = type + ".png";
        window->drawImage(filename, col * squareSize + 5, row * squareSize + 5); 
        AlienBase* occupant = galaxy->getOccupant(row, col);
        if (occupant != nullptr) {
            string name = galaxy->getOccupant(row, col)->getName();
            window->setColor("white");
            window->drawString(name.substr(0 , 1), col * squareSize, row * squareSize);
        }
    }
}

void GalaxyGUI::drawSpaceship(SpaceObject* spaceship, int row, int col) {
    string name = ((Spaceship*)spaceship)->getOccupant()->getName();
    Moves lastMove = ((Spaceship*)spaceship)->getLastMove();
    string imageFile = getShipImage(name, lastMove);
    window->drawImage(imageFile, col * squareSize + 5, row * squareSize + 5);
}

void GalaxyGUI::drawExplosion(SpaceObject* explosion, int row, int col) {
    int stage = ((Explosion*)explosion)->getStage();
    string name = ((Explosion*)explosion)->getName();
    if (stage > 0) {
        string image = name + to_string(stage) + ".png";
        ((Explosion*)explosion)->decrementStage();
        window->drawImage(image, col * squareSize, row * squareSize);
    } else {
        explosion = nullptr;
    }
}

string GalaxyGUI::getShipImage(string name, Moves lastMove) const {
    return name + moveStrings[lastMove] + ".png";
}