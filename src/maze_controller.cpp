#include <maze_controller.h>



MazeController::MazeController(){
    maze = new Cell*[GRID_WIDTH];
    bool init_walls[4] = {true, true, true, true};
    for(int i = 0; i < GRID_WIDTH; i++){
        maze[i] = new Cell[GRID_HEIGHT];
        for(int j = 0; j < GRID_HEIGHT; j++){
            maze[i][j] = Cell(i,j,init_walls);
        }
    }
}


MazeController::~MazeController(){
    for(int i = 0; i < GRID_WIDTH; i++){
        delete [] maze[i];
    }
    delete [] maze;
}

