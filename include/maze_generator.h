#ifndef MAZE_SOLVER_MAZE_GENERATOR
#define MAZE_SOLVER_MAZE_GENERATOR

#include <cell.h>

/*************************************************************************
 * MazeController object definition
 ************************************************************************/ 
class MazeController{

public:
    MazeController();
    virtual ~MazeController(); // Review Destructors

    Cell** GetMaze(){return maze;}
    void GenerateRandomMaze(Cell current_cell);

private:

    // bool IsCellVisited(int xCoord, int yCoord) const;
    void UpdateCellWalls(Cell c, DIRECTION dir);

    Cell** maze;

};

#endif