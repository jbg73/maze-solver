#include <maze_controller.h>


MazeController::MazeController(){
    maze = new Cell*[globals::GRID_WIDTH];
    bool init_walls[4] = {true, true, true, true};
    for(int i = 0; i < globals::GRID_WIDTH; i++){
        maze[i] = new Cell[globals::GRID_HEIGHT];
        for(int j = 0; j < globals::GRID_HEIGHT; j++){
            maze[i][j] = Cell(i,j,init_walls);
        }
    }

    SDL_Init(SDL_INIT_VIDEO);
    InitializeUI();
}


MazeController::~MazeController(){
    for(int i = 0; i < globals::GRID_WIDTH; i++){
        delete [] maze[i];
    }
    delete [] maze;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MazeController::InitializeUI(){
    window = SDL_CreateWindow("Maze Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::APP_WIDTH, globals::APP_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);
}


void MazeController::DrawGrid() const{
    // Set the color for drawing walls
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
    
    std::vector<std::pair<int, int>> cell_edges(4);

    for(int i = 0; i < globals::GRID_WIDTH; i++){
        for(int j = 0; j < globals::GRID_HEIGHT; j++){
            cell_edges = maze[i][j].GetCellEdges();
            if(maze[i][j].walls[0]) SDL_RenderDrawLine(renderer, cell_edges[0].first, cell_edges[0].second, cell_edges[1].first, cell_edges[1].second);
            if(maze[i][j].walls[1]) SDL_RenderDrawLine(renderer, cell_edges[1].first, cell_edges[1].second, cell_edges[2].first, cell_edges[2].second);
            if(maze[i][j].walls[2]) SDL_RenderDrawLine(renderer, cell_edges[2].first, cell_edges[2].second, cell_edges[3].first, cell_edges[3].second);
            if(maze[i][j].walls[3]) SDL_RenderDrawLine(renderer, cell_edges[3].first, cell_edges[3].second, cell_edges[0].first, cell_edges[0].second);
        }
    }

}

void MazeController::PaintCell(Cell* c, int r, int g, int b) const{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect = {c->x * (globals::CELL_SIZE), c->y * (globals::CELL_SIZE), globals::CELL_SIZE, globals::CELL_SIZE};
    SDL_RenderFillRect(renderer, &rect);
}

void MazeController::ShowWindow() const{
    SDL_RenderPresent(renderer);
}

void MazeController::ShowPath(std::vector<Cell*> visited_cells, std::vector<Cell*> current_path) const{
    for(int i = 0; i < globals::GRID_WIDTH; i++){
        for(int j = 0; j < globals::GRID_HEIGHT; j++){
            PaintCell(&maze[i][j], 0, 0, 0);
        }
    }
    SDL_SetRenderDrawColor(renderer, 200, 200, 220, 100);
    for(auto c : visited_cells){
        SDL_Rect rect = {c->x * (globals::CELL_SIZE), c->y * (globals::CELL_SIZE), globals::CELL_SIZE, globals::CELL_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (auto c : current_path){
        SDL_Rect rect = {c->x * (globals::CELL_SIZE), c->y * (globals::CELL_SIZE), globals::CELL_SIZE, globals::CELL_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }
    // Target Cell
    Cell* target_cell = *current_path.begin();
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect target_rect = {target_cell->x * (globals::CELL_SIZE), target_cell->y * (globals::CELL_SIZE), globals::CELL_SIZE, globals::CELL_SIZE};
    SDL_RenderFillRect(renderer, &target_rect);
    
    // Starting Cell
    Cell* starting_cell = current_path[current_path.size()-1];
    SDL_SetRenderDrawColor(renderer, 255, 191, 0, 255);
    SDL_Rect start_rect = {starting_cell->x * (globals::CELL_SIZE), starting_cell->y * (globals::CELL_SIZE), globals::CELL_SIZE, globals::CELL_SIZE};
    SDL_RenderFillRect(renderer, &start_rect);

    DrawGrid();

    SDL_RenderPresent(renderer);
}


