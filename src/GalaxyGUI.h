#include "Galaxy.h"
#include "gwindow.h"
#include "gradiobutton.h"

#include <string>
using namespace sgl;

class GalaxyGUI {
private:
    GWindow* window;
    Galaxy* galaxy;
    int windowSize;
    int squareSize;
    long currentTurn;
    string backgroundImage;
    static const vector<string> moveStrings;
    static const vector<string> mapFiles;
public:
    GalaxyGUI(int windowSize, int squareSize);
    void setMapFile();
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
