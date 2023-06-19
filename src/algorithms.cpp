#include <algorithms.h>
#include <globals.h>

Algorithms::Algorithms(Cell **maze_ref, UIController& ui_controller_ref) : ui_controller{ui_controller_ref}
{
    maze = maze_ref;
}

Algorithms::~Algorithms(){
    // delete maze;
    // SDL_DestroyRenderer(renderer);
}

bool Algorithms::IsVisited(Cell* cell) const{
    for(int i = 0; i < visited_cells.size(); i++){
        if(visited_cells[i]->x == cell->x && visited_cells[i]->y == cell->y)
            return true;
    }
    return false;
}

void Algorithms::UpdateCellWalls(Cell* c, DIRECTION dir){
    switch(dir){
        case UP:
            c->walls[UP] = false;
            maze[c->x][c->y-1].walls[DOWN] = false;
            break;

        case RIGHT:
            c->walls[RIGHT] = false;
            maze[c->x+1][c->y].walls[LEFT] = false;
            break;

        case DOWN:
            c->walls[DOWN] = false;
            maze[c->x][c->y+1].walls[UP] = false;
            break;

        case LEFT:
            c->walls[LEFT] = false;
            maze[c->x-1][c->y].walls[RIGHT] = false;
            break;

        case NONE:
            break;
        
        default:
            break;
    }
}

Cell* Algorithms::GetNextCell(Cell* current_cell, DIRECTION dir){
    switch(dir){
        case UP:
            return &maze[current_cell->x][current_cell->y-1];
            break;
        
        case RIGHT:
            return &maze[current_cell->x+1][current_cell->y];
            break;

        case DOWN:
            return &maze[current_cell->x][current_cell->y+1];
            break;

        case LEFT:
            return &maze[current_cell->x-1][current_cell->y];
            break;

        case NONE:
            break;

        default:
            return nullptr;
    }
    return nullptr;
}

void Algorithms::GenerateRandomMaze(Cell* current_cell){
    visited_cells.push_back(current_cell);
    // current_cell->visited_neighbours.push_back(maze[current_cell->x][current_cell->y]);
    while(current_cell->HasNonVisitedNeighbours()){
        DIRECTION next_dir = SelectRandomPossibleDirectionGenerating(current_cell);
        if(next_dir == NONE) return;
        UpdateCellWalls(current_cell, next_dir);
        // Cell next_cell = current_cell.GetNextCell(next_dir);
        // DisplayVisitedCells();
        Cell* next_cell = GetNextCell(current_cell, next_dir);
        GenerateRandomMaze(next_cell);
    }
    
}

// void Algorithms::SolveA_Star(Cell current_cell){
//     actual_time = std::chrono::high_resolution_clock::now();
//     ui_controller.PaintCell(current_cell);
//     SDL_RenderPresent(ui_controller.GetRenderer());
//     SDL_Delay(10);
//     std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(actual_time - start_time).count() << std::endl;
//     if(std::chrono::duration_cast<std::chrono::milliseconds>(actual_time - start_time).count() > 5000) return;
//     else{
//         int v1 = rand() % 4;
//         Cell next_cell = current_cell.GetNextCell(static_cast<DIRECTION>(v1));
//         SolveA_Star(next_cell);
        
//     }

// }

void Algorithms::BruteForce(Cell* current_cell){
    visited_cells.push_back(current_cell);
    ui_controller.ShowPath(visited_cells, maze);
    // ui_controller.PaintCell(current_cell);
    // SDL_RenderPresent(ui_controller.GetRenderer());
    SDL_Delay(1);
    if(current_cell->x == GRID_WIDTH-1 && current_cell->y == GRID_HEIGHT-1){
        std::cout << "Found last cell" << std::endl;
        ui_controller.PaintCell(current_cell, 255,0,0);
        SDL_RenderPresent(ui_controller.GetRenderer());
        SDL_Delay(5);
        // visited_cells.pop_back();
        solved = true;
        return;
    }
    
    else{
        while(current_cell->HasLegalNonVisitedNeighbours() && !solved){
            DIRECTION next_dir = SelectRandomPossibleDirection(current_cell);
            if(next_dir != NONE){
                Cell* next_cell = GetNextCell(current_cell, next_dir);
                current_cell->visited_neighbours.push_back(next_dir);
                next_cell->UpdateVisitedNeighbours(next_dir);
                BruteForce(next_cell);
            }
        }
    }

}

DIRECTION Algorithms::SelectRandomPossibleDirection(Cell* current_cell){

    std::vector<DIRECTION> possible_dirs;

    
    if(current_cell->y-1 >= 0 && !current_cell->walls[UP] && !IsVisited(&maze[current_cell->x][current_cell->y-1])){ //Check UP
        possible_dirs.push_back(UP);
    } 
    if(current_cell->x+1 < GRID_WIDTH && !current_cell->walls[RIGHT] && !IsVisited(&maze[current_cell->x+1][current_cell->y])){ //Check RIGHT
        possible_dirs.push_back(RIGHT);
    }
    if(current_cell->y+1 < GRID_HEIGHT && !current_cell->walls[DOWN] && !IsVisited(&maze[current_cell->x][current_cell->y+1])){ //Check DOWN
        possible_dirs.push_back(DOWN);
    }
    if(current_cell->x-1 >= 0 && !current_cell->walls[LEFT] && !IsVisited(&maze[current_cell->x-1][current_cell->y])){ //Check LEFT
        possible_dirs.push_back(LEFT);
    }

    if(possible_dirs.size() > 0){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, possible_dirs.size() - 1);
        return possible_dirs[dist(rng)];
    }

    return NONE;
}

DIRECTION Algorithms::SelectRandomPossibleDirectionGenerating(Cell* current_cell){

    std::vector<DIRECTION> possible_dirs;

    
    if(current_cell->y-1 >= 0 && current_cell->walls[UP] && !IsVisited(&maze[current_cell->x][current_cell->y-1])){ //Check UP
        possible_dirs.push_back(UP);
    } 
    if(current_cell->x+1 < GRID_WIDTH && current_cell->walls[RIGHT] && !IsVisited(&maze[current_cell->x+1][current_cell->y])){ //Check RIGHT
        possible_dirs.push_back(RIGHT);
    }
    if(current_cell->y+1 < GRID_HEIGHT && current_cell->walls[DOWN] && !IsVisited(&maze[current_cell->x][current_cell->y+1])){ //Check DOWN
        possible_dirs.push_back(DOWN);
    }
    if(current_cell->x-1 >= 0 && current_cell->walls[LEFT] && !IsVisited(&maze[current_cell->x-1][current_cell->y])){ //Check LEFT
        possible_dirs.push_back(LEFT);
    }

    if(possible_dirs.size() > 0){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, possible_dirs.size() - 1);
        return possible_dirs[dist(rng)];
    }

    return NONE;
}
