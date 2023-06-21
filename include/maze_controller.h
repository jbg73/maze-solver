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
    /**
     * @brief Construct a new Maze Controller object
     */
    MazeController();
    /**
     * @brief Construct a new Maze Controller object
     * @param maze_controller_ref Copy constructor
     */
    MazeController(const MazeController& maze_controller_ref);
    /**
     * @brief Destroy the Maze Controller object and frees all its allocated memory
     * 
     */
    virtual ~MazeController(); // Review Destructors
    /**
     * @return The maze
     */
    Cell** GetMaze() const{return maze;}
    /**
     * @return The UI renderer
     */
    SDL_Renderer* GetRenderer(){return renderer;}
    /**
     * @brief Draws the maze based on its current state 
     * @details Iterates through all the cells and draws the appropriate walls
     */
    void DrawGrid() const;
    /**
     * @brief Renders the maze and displays it
     */
    void ShowWindow() const;
    /**
     * @brief Iterates through the visited cells vector and draws a rectangle for each of them.
     * For the last position (current cell), it changes the colour to highlight it.
     * @param visited_cells vector containing the current visited cells
     */
    void ShowPath(std::vector<Cell*> visited_cells) const;
    /**
    * @brief Paints the cell from the argument in the specified colour (Orange by default)
    * @param Cell to paint
    * @param r R channel value (0-255) 
    * @param g G channel value (0-255) 
    * @param b B channel value (0-255) 
    */
    void PaintCell(Cell* c, int r=255, int g=165, int b=0) const;

private:

    /**
    * @brief Creates the UI Window and the renderer
    */
    void InitializeUI(); 

    /**
    * @brief maze object
    */
    Cell** maze;
    /**
    * @brief UI window
    */
    SDL_Window* window;
    /**
    * @brief UI renderer
    */
    SDL_Renderer* renderer;
};

#endif
