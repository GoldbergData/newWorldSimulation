/*class CritterGui {
    GWindow* window;
    CritterWorld* world;
    int windowSize;
    int squareSize;
public:
    CritterGui(int windowSize, int squareSize);
    void redraw();
};*/

#include "Galaxy.h"
#include "gwindow.h"
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
public:
    GalaxyGUI(int windowSize, int squareSize);
    void redraw();
    string getImage(string name, Moves lastMove);
};
