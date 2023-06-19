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

// void MazeController::UpdateCellWalls(Cell* c, DIRECTION dir){
//     switch(dir){
//         case UP:
//             c->walls[DOWN] = false;
//             break;

//         case RIGHT:
//             c->walls[LEFT] = false;
//             break;

//         case DOWN:
//             c->walls[UP] = false;
//             break;

//         case LEFT:
//             c->walls[RIGHT] = false;
//             break;

//         case NONE:
//             break;
        
//         default:
//             break;
//     }
//     // // Open wall current cell TO direction
//     // maze[c.x][c.y].walls[dir] = false;

//     // // Open wall next cell FROM direction
//     // switch(dir){
//     //     case UP: //UP
//     //         maze[c.x][c.y-1].walls[DOWN] = false;
//     //         break;
        
//     //     case RIGHT: //RIGHT
//     //         maze[c.x+1][c.y].walls[LEFT] = false;
//     //         break;
        
//     //     case DOWN: //DOWN
//     //         maze[c.x][c.y+1].walls[UP] = false;
//     //         break;
        
//     //     case LEFT: //LEFT
//     //         maze[c.x-1][c.y].walls[RIGHT] = false;
//     //         break;
        
//     //     default:
//     //         break;
//     // }
// }

// void MazeController::GenerateRandomMaze(Cell* current_cell){
//     current_cell->visited_cells.push_back(maze[current_cell->x][current_cell->y]);
//     while(current_cell->HasNonVisitedNeighbours()){
//         DIRECTION next_dir = current_cell.SelectRandomPossibleDirection();
//         UpdateCellWalls(current_cell, next_dir);
//         Cell next_cell = current_cell.GetNextCell(next_dir);
//         // DisplayVisitedCells();
//         GenerateRandomMaze(maze[next_cell.x][next_cell.y]);
//     }
    
// }

