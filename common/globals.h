#ifndef MAZE_SOLVER_GLOBALS_H
#define MAZE_SOLVER_GLOBALS_H

/************************************************************************
 * Global Variables Definition 
 ***********************************************************************/
namespace globals
{
    const int APP_WIDTH = 1200;
    const int APP_HEIGHT = 801;
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;
    const int CELL_SIZE = 20;
    const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
    const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

    enum DIRECTION
    {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        NONE
    };

}

#endif