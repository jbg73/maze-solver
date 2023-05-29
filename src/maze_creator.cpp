#include <iostream>
// #include <SDL.h>

#include <SDL2/SDL.h>
#include <vector>
#include <random>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 480;
const int CELL_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

enum DIRECTION {UP, RIGHT, DOWN, LEFT, NONE};

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

typedef std::vector<Cell> t_vcells;
t_vcells visited_cells;

void InitializeMaze(Cell** maze){

    bool walls[4] = {true,true,true,true};
    for(int i = 0; i < WINDOW_WIDTH; i++){
        maze[i] = new Cell[WINDOW_HEIGHT];
        for(int j = 0; j < WINDOW_HEIGHT; j++){
            maze[i][j] = Cell(i,j,walls);
        }
    }
    
}

void DisplayCellStatus(const Cell* c){
    std::cout << "Position: (" << c->x << ", " << c->y << ")" << "\t" << "N:" << c->walls[0] << " E:" << c->walls[1] << " S:" << c->walls[2] << " W:" << c->walls[3] << std::endl;
}

bool IsCellVisited(int xCoord, int yCoord){
    for(int i = 0; i < visited_cells.size(); i++){
        if(visited_cells[i].x == xCoord && visited_cells[i].y == yCoord) 
            return true;
    }
    return false;
}


void UpdateCellWalls(Cell** maze, Cell c, int dir){
    // Open wall current cell TO direction
    maze[c.x][c.y].walls[dir] = false;

    // Open wall next cell FROM direction
    switch(dir){
        case 0: //UP
            maze[c.x][c.y-1].walls[DOWN] = false;
            break;
        
        case 1: //RIGHT
            maze[c.x+1][c.y].walls[LEFT] = false;
            break;
        
        case 2: //DOWN
            maze[c.x][c.y+1].walls[UP] = true;
            break;
        
        case 3: //LEFT
            maze[c.x-1][c.y].walls[RIGHT] = false;
            break;
        
        default:
            break;
    }
}

bool HasNonVisitedNeighbours(Cell current_cell){
    
    //Check UP
    if(current_cell.y-1 >= 0 && !IsCellVisited(current_cell.x, current_cell.y-1)) return true;
    //Check RIGHT
    if(current_cell.x+1 < WINDOW_WIDTH && !IsCellVisited(current_cell.x+1, current_cell.y)) return true;
    //Check Bottom
    if(current_cell.y+1 < WINDOW_HEIGHT && !IsCellVisited(current_cell.x, current_cell.y+1)) return true;
    //Check left
    if(current_cell.x-1 >= 0 && !IsCellVisited(current_cell.x-1, current_cell.y)) return true;

    return false;
}

int SelectRandomNeighbour(Cell current_cell){ // Problema con lo que se esta devolviendo

    std::vector<int> non_visited_neighbours;
    //Check UP
    if(current_cell.y-1 >= 0 && !IsCellVisited(current_cell.x, current_cell.y-1)) non_visited_neighbours.push_back(0);
    //Check RIGHT
    if(current_cell.x+1 < WINDOW_WIDTH && !IsCellVisited(current_cell.x+1, current_cell.y)) non_visited_neighbours.push_back(1);
    //Check Bottom
    if(current_cell.y+1 < WINDOW_HEIGHT && !IsCellVisited(current_cell.x, current_cell.y+1)) non_visited_neighbours.push_back(2);
    //Check left
    if(current_cell.x-1 >= 0 && !IsCellVisited(current_cell.x-1, current_cell.y)) non_visited_neighbours.push_back(3);

    if(non_visited_neighbours.size() > 0){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, non_visited_neighbours.size() - 1);
        int selected_dir = dist(rng);
        return non_visited_neighbours[selected_dir];
    }
    return -1;
}

Cell GetNextCell(Cell current_cell, int next_dir){
    Cell next_cell;

    switch(next_dir){
        case 0: //UP
            next_cell.x = current_cell.x;
            next_cell.y = current_cell.y-1;
            break;
        
        case 1: //RIGHT
            next_cell.x = current_cell.x+1;
            next_cell.y = current_cell.y;
            break;
        
        case 2: //DOWN
            next_cell.x = current_cell.x;
            next_cell.y = current_cell.y+1;
            break;
        
        case 3: //LEFT
            next_cell.x = current_cell.x-1;
            next_cell.y = current_cell.y;
            break;
        
        default:
            break;
    }
    return next_cell;

}

void DisplayVisitedCells(){
    for(int i = 0; i < visited_cells.size(); i++){
        std::cout << "(" << visited_cells[i].x << "," << visited_cells[i].y << ")" << " ";
    }
    std::cout << std::endl;
}

void GenerateRandomMaze(Cell** maze, Cell current_cell)
{
    visited_cells.push_back(maze[current_cell.x][current_cell.y]);
    while(HasNonVisitedNeighbours(current_cell)){
        int next_dir = SelectRandomNeighbour(current_cell);
        UpdateCellWalls(maze, current_cell, next_dir);
        Cell next_cell = GetNextCell(current_cell, next_dir);
        // DisplayVisitedCells();
        GenerateRandomMaze(maze, maze[next_cell.x][next_cell.y]);
    }

}

void DrawGrid(SDL_Renderer* renderer, Cell** maze){
    // Set the color for drawing walls
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
    
    // for(int i = 0; i < WINDOW_WIDTH; i++){
    //     for(int j = 0; j < WINDOW_HEIGHT; j++){
    //         if(maze[i][j].walls[0]) SDL_RenderDrawLine(renderer, )
    //     }
    // }

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

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create an SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("SDL Grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Clear the renderer
    SDL_RenderClear(renderer);
    
    Cell **maze = new Cell*[WINDOW_WIDTH];
    InitializeMaze(maze);
    GenerateRandomMaze(maze, maze[1][1]);

    DrawGrid(renderer, maze);

    
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
    for(int i = 0; i < WINDOW_WIDTH; i++){
        delete [] maze[i];
    }
    delete [] maze;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
