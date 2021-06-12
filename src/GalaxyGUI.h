#include "Galaxy.h"
#include "gwindow.h"
#include "gradiobutton.h"

#include <string>
using namespace sgl;

const vector<string> moveStrings = {"C", "N", "E", "S", "W", "NE", "NW", "SE", "SW"};

class GalaxyGUI {
private:
    GWindow* window;
    Galaxy* galaxy;
    int windowSize;
    int squareSize;
    long currentTurn;
    string backgroundImage;
public:
    GalaxyGUI(int windowSize, int squareSize);
    void checkImage();
    void setImage(string imageFile);
    void createButtons();
    void createSingleRadio(string text, GRadioButton** nameOut);
    void createRadioButtons();
    void tick();
    void redraw();
    void drawSpaceObject(SpaceObject* spaceObject, int row, int col);
    void drawSpaceship(SpaceObject* spaceship, int row, int col);
    void drawExplosion(SpaceObject* explosion, int row, int col);
    string getShipImage(string name, Moves lastMove) const;
};
