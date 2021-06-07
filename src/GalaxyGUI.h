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
using namespace std;

class GalaxyGUI {
private:
    GWindow* window;
    Galaxy* world;
    int windowSize;
    int squareSize;
public:
    GalaxyGUI(int windowSize, int squareSize);
}