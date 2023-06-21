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
    // void GenerateRandomMaze(Cell current_cell);

    SDL_Renderer* GetRenderer(){return renderer;}
    void DrawGrid(Cell** maze) const;
    void PaintCell(Cell* c, int r=255, int g=165, int b=0) const;
    void ShowWindow() const;
    void ShowPath(std::vector<Cell*> visited_cells, Cell** maze);

private:

    // bool IsCellVisited(int xCoord, int yCoord) const;
    void UpdateCellWalls(Cell c, DIRECTION dir);

    void InitializeUI(); 

    Cell** maze;

    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif