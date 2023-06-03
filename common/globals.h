#ifndef MAZE_SOLVER_GLOBALS_H
#define MAZE_SOLVER_GLOBALS_H

/************************************************************************
 * Global Variables Definition 
 ***********************************************************************/
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 50;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

enum DIRECTION {UP, RIGHT, DOWN, LEFT, NONE};

#endif