#include <iostream>
// #include <SDL.h>

#include <SDL2/SDL.h>
#include <vector>
#include <random>
#include <maze_generator.h>




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

void MazeController::UpdateCellWalls(Cell c, DIRECTION dir){
    // Open wall current cell TO direction
    maze[c.x][c.y].walls[dir] = false;

    // Open wall next cell FROM direction
    switch(dir){
        case UP: //UP
            maze[c.x][c.y-1].walls[DOWN] = false;
            break;
        
        case RIGHT: //RIGHT
            maze[c.x+1][c.y].walls[LEFT] = false;
            break;
        
        case DOWN: //DOWN
            maze[c.x][c.y+1].walls[UP] = false;
            break;
        
        case LEFT: //LEFT
            maze[c.x-1][c.y].walls[RIGHT] = false;
            break;
        
        default:
            break;
    }
}

void MazeController::GenerateRandomMaze(Cell current_cell){
    current_cell.visited_cells.push_back(maze[current_cell.x][current_cell.y]);
    while(current_cell.HasNonVisitedNeighbours()){
        DIRECTION next_dir = current_cell.SelectRandomPossibleDirection();
        UpdateCellWalls(current_cell, next_dir);
        Cell next_cell = current_cell.GetNextCell(next_dir);
        // DisplayVisitedCells();
        GenerateRandomMaze(maze[next_cell.x][next_cell.y]);
    }
}


void DrawGrid(SDL_Renderer* renderer, Cell** maze){
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

    SDL_RenderPresent(renderer);
}

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create an SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("SDL Grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH+1, WINDOW_HEIGHT+1, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Clear the renderer
    SDL_RenderClear(renderer);
    
    MazeController* maze_controller = new MazeController();

    bool walls[4] = {true,true,true,true};
    Cell initial_cell(0, 0, walls);
    maze_controller->GenerateRandomMaze(initial_cell);

    // Cell **maze = new Cell*[GRID_WIDTH];
    // InitializeMaze(maze);
    // GenerateRandomMaze(maze, maze[0][0]);

    std::cout << "Maze generated" << std::endl;

    DrawGrid(renderer, maze_controller->GetMaze());

    
    // Wait for a key press to exit
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
                quit = true;
            }
        }
    }
    
    delete maze_controller;

    // Cleanup and quit SDL
    // for(int i = 0; i < GRID_WIDTH; i++){
    //     delete [] maze[i];
    // }
    // delete [] maze;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
