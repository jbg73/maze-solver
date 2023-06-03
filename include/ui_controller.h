#ifndef MAZE_SOLVER_UI_CONTROLLER_H
#define MAZE_SOLVER_UI_CONTROLLER_H

#include <SDL2/SDL.h>
#include <cell.h>
#include <globals.h>

class UIController{

public:

    UIController();
    ~UIController();

    SDL_Renderer* GetRenderer(){return renderer;}
    void DrawGrid(Cell** maze) const;
    void PaintCell(Cell c, int r=255, int g=165, int b=0) const;
    void ShowWindow() const;
    void ShowPath(std::vector<Cell> visited_cells, Cell** maze);
private:

    void InitializeUI(); 

    SDL_Window* window;
    SDL_Renderer* renderer;

};

#endif