#include <iostream>
// #include <SDL.h>

#include <SDL2/SDL.h>
#include <vector>
#include <random>

/************************************************************************
 * Global Variables Definition 
 ***********************************************************************/
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 10;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

enum DIRECTION {UP, RIGHT, DOWN, LEFT, NONE};


/***********************************************************************
 * Cell object definition
 ***********************************************************************/ 
struct Cell{
    int x;
    int y;
    bool walls[4];
    static std::vector<Cell> visited_cells;

    Cell() : x{0}, y{0}, walls{true,true,true,true}{}
    Cell(int x_val, int y_val, bool walls_vals[4]) : x{x_val}, y{y_val}{
        for(int i = 0; i < 4; i++){
            walls[i] = walls_vals[i];
        }
    }

    bool IsCellVisited() const;
    bool IsCellVisited(int pos_x, int pos_y) const;
    bool HasNonVisitedNeighbours() const;
    int SelectRandomPossibleDirection() const;
    Cell GetNextCell(int dir) const;
    std::vector<std::pair<int,int>> GetCellEdges() const;
};

std::vector<Cell> Cell::visited_cells;

bool Cell::IsCellVisited() const{
    for(int i = 0; i < visited_cells.size(); i++){
        if(visited_cells[i].x == x && visited_cells[i].y == y) 
            return true;
    }
    return false;
}

bool Cell::IsCellVisited(int pos_x, int pos_y) const{
    for(int i = 0; i < visited_cells.size(); i++){
        if(visited_cells[i].x == pos_x && visited_cells[i].y == pos_y) 
            return true;
    }
    return false;
}

bool Cell::HasNonVisitedNeighbours() const{
    //Check UP
    if(y-1 >= 0 && !IsCellVisited(x, y-1)) return true;
    //Check RIGHT
    if(x+1 < GRID_WIDTH && !IsCellVisited(x+1, y)) return true;
    //Check Bottom
    if(y+1 < GRID_HEIGHT && !IsCellVisited(x, y+1)) return true;
    //Check left
    if(x-1 >= 0 && !IsCellVisited(x-1, y)) return true;

    return false;
}

int Cell::SelectRandomPossibleDirection() const{
    std::vector<int> non_visited_neighbours;
    //Check UP
    if(y-1 >= 0 && !IsCellVisited(x, y-1)) non_visited_neighbours.push_back(0);
    //Check RIGHT
    if(x+1 < GRID_WIDTH && !IsCellVisited(x+1, y)) non_visited_neighbours.push_back(1);
    //Check Bottom
    if(y+1 < GRID_HEIGHT && !IsCellVisited(x, y+1)) non_visited_neighbours.push_back(2);
    //Check left
    if(x-1 >= 0 && !IsCellVisited(x-1, y)) non_visited_neighbours.push_back(3);

    if(non_visited_neighbours.size() > 0){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, non_visited_neighbours.size() - 1);
        int selected_dir = dist(rng);
        return non_visited_neighbours[selected_dir];
    }
    return -1;
}

Cell Cell::GetNextCell(int dir) const{
    Cell next_cell;

    switch(dir){
        case 0: //UP
            next_cell.x = x;
            next_cell.y = y-1;
            break;
        
        case 1: //RIGHT
            next_cell.x = x+1;
            next_cell.y = y;
            break;
        
        case 2: //DOWN
            next_cell.x = x;
            next_cell.y = y+1;
            break;
        
        case 3: //LEFT
            next_cell.x = x-1;
            next_cell.y = y;
            break;
        
        default:
            break;
    }
    return next_cell;
}

std::vector<std::pair<int,int>> Cell::GetCellEdges() const{
    std::vector<std::pair<int,int>> cell_edges(4);

    cell_edges[0] = std::make_pair(x*CELL_SIZE, y*CELL_SIZE); // top left
    cell_edges[1] = std::make_pair((x+1)*CELL_SIZE, y*CELL_SIZE); // top right
    cell_edges[2] = std::make_pair((x+1)*CELL_SIZE, (y+1)*CELL_SIZE); // bottom right
    cell_edges[3] = std::make_pair(x*CELL_SIZE, (y+1)*CELL_SIZE); // bottom left

    return cell_edges;
}

/*************************************************************************
 * MazeController object definition
 ************************************************************************/ 
class MazeController{

public:
    MazeController();
    virtual ~MazeController(); // Review Destructors

    Cell** GetMaze(){return maze;}
    void GenerateRandomMaze(Cell current_cell);

private:

    // bool IsCellVisited(int xCoord, int yCoord) const;
    void UpdateCellWalls(Cell c, int dir);

    Cell** maze;


};

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

void MazeController::UpdateCellWalls(Cell c, int dir){
    // Open wall current cell TO direction
    maze[c.x][c.y].walls[dir] = false;

    // Open wall next cell FROM direction
    switch(dir){
        case 0: //UP
            maze[c.x][c.y-1].walls[2] = false;
            break;
        
        case 1: //RIGHT
            maze[c.x+1][c.y].walls[3] = false;
            break;
        
        case 2: //DOWN
            maze[c.x][c.y+1].walls[0] = false;
            break;
        
        case 3: //LEFT
            maze[c.x-1][c.y].walls[1] = false;
            break;
        
        default:
            break;
    }
}

void MazeController::GenerateRandomMaze(Cell current_cell){
    current_cell.visited_cells.push_back(maze[current_cell.x][current_cell.y]);
    while(current_cell.HasNonVisitedNeighbours()){
        int next_dir = current_cell.SelectRandomPossibleDirection();
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
