/**
 * @file GalaxyGUI.h
 * @author John Nguyen, Joshua Goldberg (jvn1567@gmail.com, J.GOLDBERG4674@edmail.edcc.edu)
 * @brief GalaxyGUI handles the visualization of the simulation computed by Galaxy
 * class. User can specify the background image, a map (objects to populate
 * in the grid). Moreover, the simulation can be started, stopped, or reset.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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

    /**
     * @brief Used to append the direction of ship image file names.
     * 
     */
    static const vector<string> moveStrings;

    /**
     * @brief Predefined maps.
     * 
     */
    static const vector<string> mapFiles;
public:
    /**
     * @brief Construct a new Galaxy GUI object.
     * 
     * @param windowSize Width/height of grid area, assuming a square.
     * @param squareSize Number of pixel per grid location.
     */
    GalaxyGUI(int windowSize, int squareSize);

    /**
     * @brief Set the Map File to load from for initial Galaxy state.
     * 
     */
    void setMapFile();

    /**
     * @brief Checks which radio button is selected, sets the background image,
     * and calls setImage().
     * 
     */
    void checkImage();

    /**
     * @brief Set the background image and redraws the simulation window.
     * 
     * @param imageFile The file name of a background image.
     */
    void setImage(string imageFile);

    /**
     * @brief Create Button objects and click/timer listeners for each button.
     * The buttons created include: SET MAP, START, STOP, and RESET. Certain
     * buttons are disabled when appropriate.
     * 
     */
    void createButtons();

    /**
     * @brief Create a single radio button object to control the background image.
     * 
     * @param text Label of radioButton.
     * @param nameOut An address of a pointer to a radio button.
     */
    void createSingleRadio(string text, GRadioButton** nameOut);

    /**
     * @brief Create radio button objects to control the background image. This
     * method also sets up a timer listener to check which radio button 
     * (background) is selected.
     * 
     */
    void createRadioButtons();

    /**
     * @brief Create a dropdown menu object that allows to change the map file
     * used to initialize the grid on start.
     * 
     */
    void createMapChooser();

    /**
     * @brief Iterates the simulation by one move.
     * 
     */
    void tick();

    /**
     * @brief Redraws the objects of the simulation window.
     * 
     */
    void redraw();

    /**
     * @brief Draws a single SpaceObject (planet or star) and the the occupants.
     * Occupants are represented by the first letter of their alien race name and
     * a percentage representing fullness of the planet with respect to max
     * population of the planet.
     * 
     * @param spaceObject Either a star or planet.
     * @param rows Vertical positioning in the simulation window.
     * @param cols Horizontal positioning in the simulation window.
     */
    void drawSpaceObject(SpaceObject* spaceObject, int row, int col);

    /**
     * @brief Draws a single Spaceship facing the direction of its last move.
     * 
     * @param spaceship A spaceship.
     * @param rows Vertical positioning in the simulation window.
     * @param cols Horizontal positioning in the simulation window.
     */
    void drawSpaceship(SpaceObject* spaceship, int row, int col);

    /**
     * @brief Draws an explosion, which occurs when a spaceship loses a battle.
     * Explosions start at a peak stage (image size) and reduce in stage (image
     * size) over nine simulation iterations. This results in an "animated"
     * explosion.
     * 
     * @param explosion An explosion.
     * @param rows Vertical positioning in the simulation window.
     * @param cols Horizontal positioning in the simulation window.
     */
    void drawExplosion(SpaceObject* explosion, int row, int col);

    /**
     * @brief Get the filename for the image of a spaceship.
     * 
     * @param name Alien type.
     * @param lastMove The last move of a spaceship used to determine which
     * spaceship image to draw.
     * @return string A filename.
     */
    string getShipImage(string name, Moves lastMove) const;
};
