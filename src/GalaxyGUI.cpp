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
#include "gchooser.h"
#include "glabel.h"
using namespace sgl;

const vector<string> GalaxyGUI::moveStrings = {"C", "N", "E", "S", "W", "NE", "NW", "SE", "SW"};
const vector<string> GalaxyGUI::mapFiles = {"Map1", "Map2"};

GRadioButton* grbBackground1;
GRadioButton* grbBackground2;
GRadioButton* grbBackground3;
GRadioButton* grbBackground4;
GButton* gbSetMap;
GButton* gbStart;
GButton* gbStop;
GButton* gbReset;
GChooser* gcMapSelect;
GLabel* glInstructions;

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
    galaxy = new Galaxy(tileCount, tileCount, "Map1.txt");
    this->windowSize = windowSize;
    this->squareSize = squareSize;
    currentTurn = 0;
    //creating buttons, other misc setup
    createMapChooser();
    createButtons();
    createRadioButtons();
<<<<<<< HEAD
=======
    gcMapSelect = new GChooser(mapFiles);
    window->setTimerListener(50, [this] {
        this->checkImage();
    });
>>>>>>> 92217f573a8e3a79f2371fcafd97f2c5614a7f84
}

void GalaxyGUI::setMapFile() {
    string filename = gcMapSelect->getSelectedItem() + ".txt";
    int tileCount = windowSize / squareSize;
    Galaxy* newGalaxy = new Galaxy(tileCount, tileCount, filename);
    galaxy = newGalaxy;
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
    gbSetMap = new GButton("SET MAP");
    gbSetMap->setClickListener([this] {
        gbStart->setEnabled(true);
        setMapFile();
    });
    gbStart = new GButton("START");
    gbStart->setClickListener([this] {
        gbSetMap->setEnabled(false);
        gbStop->setEnabled(true);
        gbStart->setEnabled(false);
        gbReset->setEnabled(false);
        //Timer listeners don't replace properly, and seem to perform the
        //actions of both listeners and using both time intervals. This
        //is a rough workaround.
        window->setTimerListener(999999, [this] {
            this->tick();
        });
    });
    gbStop = new GButton("STOP"); 
    gbStop->setClickListener([this] {
        gbReset->setEnabled(true);
        gbStart->setEnabled(true);
        gbStop->setEnabled(false);
        //Remove doesnt remove, it seems to only pause.
        window->removeTimerListener();
        //Unpauses the checker for background image selection
        window->setTimerListener(999999, [this] {
            this->checkImage();
        });
    });
    gbReset = new GButton("RESET");
    gbReset->setClickListener([this] {
        setMapFile();
        currentTurn = 0;
        gbReset->setEnabled(false);
        gbSetMap->setEnabled(true);
    });
    //initial buttons states and add
    gbStart->setEnabled(false);
    gbStop->setEnabled(false);
    gbReset->setEnabled(false);
    window->addToRegion(gbSetMap, "East");
    window->addToRegion(gbStart, "East");
    window->addToRegion(gbStop, "East");
    window->addToRegion(gbReset, "East");
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
    //checks for radio buttons being changed
    window->setTimerListener(200, [this] {
        this->checkImage();
    });
}

void GalaxyGUI::createMapChooser() {
    gcMapSelect = new GChooser(mapFiles);
    glInstructions = new GLabel("Select map to begin.");
    glInstructions->setColor("white");
    window->addToRegion(glInstructions, "East");
    window->addToRegion(gcMapSelect, "East");
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
            //grab and draw anything that's not a nullptr
            SpaceObject* spaceObject = galaxy->getSpaceObject(i, j);
            SpaceObject* spaceship = galaxy->getSpaceship(i, j);
            SpaceObject* explosion = galaxy->getExplosion(i, j);
            if (spaceObject != nullptr) {
                drawSpaceObject(spaceObject, i, j);
            }
            if (spaceship != nullptr) {
                drawSpaceship(spaceship, i, j);
            }
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