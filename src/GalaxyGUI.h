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
using namespace sgl;

class GalaxyGUI {
private:
    GWindow* window;
    Galaxy* galaxy;
    int windowSize;
    int squareSize;
    long currentTurn;
public:
    GalaxyGUI(int windowSize, int squareSize);
    void update();
    void redraw();
};
