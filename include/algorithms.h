#ifndef MAZE_SOLVER_ALGOTITHMS_H
#define MAZE_SOLVER_ALGOTITHMS_H

#include <maze_controller.h>
#include <ctime>
#include <chrono>

class Algorithms{

public:
    /**
     * @brief Default constructor is disabled
     */
    Algorithms() = delete;
    /**
     * @brief Copy constructor
     * @param maze_ref Maze reference
     * @param maze_controller_ref maze controller object reference
     */
    Algorithms(Cell **maze_ref, MazeController& maze_controller_ref);
    /**
     * @brief Destroy the Algorithms object
     */
    ~Algorithms();
    
    /**
     * @brief Starts the timer
     */
    void SetStartTime() {start_time = std::chrono::high_resolution_clock::now();}
    
    // void SolveA_Star(Cell current_cell);
    /**
     * @brief Algorithm to solve the maze from current cell until bottom-right corner using pure backtracking approach
     * 
     * @param current_cell Cell from which the algorithm begins
     */
    void BruteForce(Cell* current_cell);
    /**
     * @brief Algorithm to generate the maze
     * @details Begining at current_cell, selects a random neighbour and "breaks" the wall separating them and adds it to the list of visited cells.
     * Each cell is only visited once
     * @param current_cell Cell from which the algorithm begins
     */
    void GenerateRandomMaze(Cell* current_cell);
    /**
     * @return The maze
     */
    Cell** GetMaze() {return maze;}
    /**
     * @brief Clears the visited_cells vector
     */
    void ClearVisitedCells(){visited_cells.clear();}

private:

    /**
     * @brief Checks whether the cell received as argument has been visited
     * @param cell cell to check whether is visited or not 
     * @return true if visited, false otherwise
     */
    bool IsVisited(Cell* cell) const;
    /**
     * @brief Get the corresponding cell when moving in dir direction from current_cell
     * 
     * @param current_cell current cell from which we move
     * @param dir direction in which we move
     * @return cell reference from the maze 
     */
    Cell* GetNextCell(Cell* current_cell, DIRECTION dir);
    
    DIRECTION SelectRandomPossibleDirection(Cell* current_cell);
    DIRECTION SelectRandomPossibleDirectionGenerating(Cell* current_cell);
    /**
     * @brief Updates the cell walls from the current cell and from the cell that results from going from current cell in the direction received
     * @details if going UP from current cell, ir updates its UP wall and the next cell updates its DOWN wall
     * @param cell Cell from which the movement is executed
     * @param dir Direction in which we move from current cell
     */
    void UpdateCellWalls(Cell* cell, DIRECTION dir);
    /**
     * @brief vector of current visited cells
     */
    std::vector<Cell*> visited_cells;
    /**
     * @brief The maze
     */
    Cell** maze; 
    /**
     * @brief Maze controller reference object
     */
    MazeController& maze_controller;
    /**
     * @brief Variable to store start time
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    /**
     * @brief Variable to store the current time
     * 
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> actual_time;
    /**
     * @brief Stores if the algorithm has solved the maze or not
     * 
     */
    bool solved = false;
};

#endif
