#include <iostream>
#include <SDL.h>

#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

struct Cell{
    int x;
    int y;
    bool walls[4];

    Cell() : x{0}, y{0}, walls{true, true, true, true}{}
    Cell(int x_val, int y_val, bool walls_val[]) : x{x_val}, y{y_val}
    {
        for(int i = 0; i < 4; i++) walls[i] = walls_val[i];
    }
};


void drawGrid(SDL_Renderer* renderer) {
    // Set the color for drawing walls
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
    
    // Draw the vertical walls
    for (int x = 0; x < GRID_WIDTH; x++) {
        SDL_RenderDrawLine(renderer, x * CELL_SIZE, 0, x * CELL_SIZE, WINDOW_HEIGHT);
    }
    
    // Draw the horizontal walls
    for (int y = 0; y < GRID_HEIGHT; y++) {
        SDL_RenderDrawLine(renderer, 0, y * CELL_SIZE, WINDOW_WIDTH, y * CELL_SIZE);
    }
    
    // Update the renderer
    SDL_RenderPresent(renderer);
}

void InitializeMaze(Cell** maze){

    bool walls[4] = {true,true,true,true};
    for(int i = 0; i < WINDOW_HEIGHT; i++){
        maze[i] = new Cell[WINDOW_WIDTH];
        for(int j = 0; j < WINDOW_WIDTH; j++){
            maze[i][j] = Cell(i,j,walls);
        }
    }
    
}

void DisplayCellStatus(const Cell* c){
    std::cout << "Position: (" << c->x << ", " << c->y << ")" << "\t" << "N:" << c->walls[0] << " E:" << c->walls[1] << " S:" << c->walls[2] << " W:" << c->walls[3] << std::endl;
}

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create an SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("SDL Grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Clear the renderer
    SDL_RenderClear(renderer);
    
    Cell **maze = new Cell*[WINDOW_HEIGHT];
    InitializeMaze(maze);
    

    // Draw the grid
    drawGrid(renderer);
    
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
    
    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
