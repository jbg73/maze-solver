#ifndef MAZE_SOLVER_MAZE_GENERATOR
#define MAZE_SOLVER_MAZE_GENERATOR

#include <iostream>
#include <cell.h>
#include <SDL2/SDL.h>
#include <vector>
#include <random>

/*************************************************************************
 * MazeController object definition
 ************************************************************************/ 
class MazeController{

public:
    MazeController();
    MazeController(const MazeController& maze_controller_ref);
    virtual ~MazeController(); // Review Destructors

    Cell** GetMaze() const{return maze;}
    void GenerateRandomMaze(Cell current_cell);

private:

    // bool IsCellVisited(int xCoord, int yCoord) const;
    void UpdateCellWalls(Cell c, DIRECTION dir);

    Cell** maze;

};

#endif