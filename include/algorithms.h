#ifndef MAZE_SOLVER_ALGOTITHMS_H
#define MAZE_SOLVER_ALGOTITHMS_H

#include <maze_controller.h>
#include <ui_controller.h>
#include <ctime>
#include <chrono>

class Algorithms{

public:
    Algorithms() = delete;
    Algorithms(Cell **maze_ref, UIController& renderer_ref);
    // Algorithms(const MazeController& maze_ref, UIController& renderer_ref);
    ~Algorithms();

    bool IsVisited(Cell* cell) const;
    void SetStartTime() {start_time = std::chrono::high_resolution_clock::now();}
    Cell* GetNextCell(Cell* current_cell, DIRECTION dir);
    // void SolveA_Star(Cell current_cell);
    void BruteForce(Cell* current_cell);
    void GenerateRandomMaze(Cell* current_cell);
    Cell** GetMaze() {return maze;}
    void ClearVisitedCells(){visited_cells.clear();}

private:

    DIRECTION SelectRandomPossibleDirection(Cell* current_cell);
    DIRECTION SelectRandomPossibleDirectionGenerating(Cell* current_cell);
    void UpdateCellWalls(Cell* cell, DIRECTION dir);
    std::vector<Cell*> visited_cells;
    Cell** maze; 
    UIController& ui_controller;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> actual_time;
    bool solved = false;
};

#endif