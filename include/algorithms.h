#ifndef MAZE_SOLVER_ALGOTITHMS_H
#define MAZE_SOLVER_ALGOTITHMS_H

#include <maze_controller.h>
#include <ui_controller.h>
#include <ctime>
#include <chrono>

class Algorithms{

public:
    Algorithms() = delete;
    Algorithms(const MazeController& maze_ref, UIController& renderer_ref);
    ~Algorithms();

    void SetStartTime() {start_time = std::chrono::high_resolution_clock::now();}
    void SolveA_Star(Cell current_cell);
    void BruteForce(Cell current_cell);

private:

    DIRECTION SelectRandomPossibleDirection(Cell current_cell);

    std::vector<Cell> visited_cells;
    Cell** maze; 
    UIController& ui_controller;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> actual_time;
};

#endif