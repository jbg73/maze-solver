#include <ui_controller.h>


UIController::UIController(){
    SDL_Init(SDL_INIT_VIDEO);
    InitializeUI();
}

void UIController::InitializeUI(){
    window = SDL_CreateWindow("Maze Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH+1, WINDOW_HEIGHT+1, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);
}

UIController::~UIController(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void UIController::DrawGrid(Cell** maze) const{
    // Set the color for drawing walls
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
    
    std::vector<std::pair<int, int>> cell_edges(4);

    for(int i = 0; i < GRID_WIDTH; i++){
        for(int j = 0; j < GRID_HEIGHT; j++){
            cell_edges = maze[i][j].GetCellEdges();
            if(maze[i][j].walls[0]) SDL_RenderDrawLine(renderer, cell_edges[0].first, cell_edges[0].second, cell_edges[1].first, cell_edges[1].second);
            if(maze[i][j].walls[1]) SDL_RenderDrawLine(renderer, cell_edges[1].first, cell_edges[1].second, cell_edges[2].first, cell_edges[2].second);
            if(maze[i][j].walls[2]) SDL_RenderDrawLine(renderer, cell_edges[2].first, cell_edges[2].second, cell_edges[3].first, cell_edges[3].second);
            if(maze[i][j].walls[3]) SDL_RenderDrawLine(renderer, cell_edges[3].first, cell_edges[3].second, cell_edges[0].first, cell_edges[0].second);
        }
    }

}

void UIController::PaintCell(Cell c, int r, int g, int b) const{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect = {c.x * CELL_SIZE, c.y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_RenderFillRect(renderer, &rect);
}

void UIController::ShowWindow() const{
    SDL_RenderPresent(renderer);
}