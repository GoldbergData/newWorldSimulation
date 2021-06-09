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
    void spawnShip(int row, int col, AlienBase* occupant, Galaxy* galaxy);
    void moveShips();
    bool updatePopulation(SpaceObject* spaceObject, AlienBase* occupant);
    void moveSpaceObject(int row, int col, SpaceObject* spaceObject, Galaxy* newGalaxy);
    void generateTestGalaxy();
    void generateGalaxyFile(string filename);
};
