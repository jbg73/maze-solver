#include <algorithms.h>
#include <globals.h>

Algorithms::Algorithms(const MazeController& maze_controller_ref, UIController& ui_controller_ref) : ui_controller{ui_controller_ref}{
    maze = maze_controller_ref.GetMaze();
    
}

Algorithms::~Algorithms(){
    // delete maze;
    // SDL_DestroyRenderer(renderer);
}

void Algorithms::SolveA_Star(Cell current_cell){
    actual_time = std::chrono::high_resolution_clock::now();
    ui_controller.PaintCell(current_cell);
    SDL_RenderPresent(ui_controller.GetRenderer());
    SDL_Delay(10);
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(actual_time - start_time).count() << std::endl;
    if(std::chrono::duration_cast<std::chrono::milliseconds>(actual_time - start_time).count() > 5000) return;
    else{
        int v1 = rand() % 4;
        Cell next_cell = current_cell.GetNextCell(static_cast<DIRECTION>(v1));
        SolveA_Star(next_cell);
        
    }

}

void Algorithms::BruteForce(Cell current_cell){
    visited_cells.push_back(current_cell);
    ui_controller.ShowPath(visited_cells, maze);
    // ui_controller.PaintCell(current_cell);
    // SDL_RenderPresent(ui_controller.GetRenderer());
    SDL_Delay(2);
    if(current_cell.x == GRID_WIDTH-1 && current_cell.y == GRID_HEIGHT-1){
        std::cout << "Found last cell" << std::endl;
        ui_controller.PaintCell(current_cell, 255,0,0);
        SDL_RenderPresent(ui_controller.GetRenderer());
        SDL_Delay(5);
        visited_cells.pop_back();
        return;
    }

    else{
        DIRECTION next_dir = SelectRandomPossibleDirection(current_cell);
        if(next_dir != NONE){
            Cell next_cell = maze[current_cell.GetNextCell(next_dir).x][current_cell.GetNextCell(next_dir).y];
            BruteForce(next_cell);
        }
    }

}

DIRECTION Algorithms::SelectRandomPossibleDirection(Cell current_cell){

    std::vector<DIRECTION> possible_dirs;

    
    if(!current_cell.walls[UP] && !current_cell.IsCellVisited(UP)){ //Check UP
        possible_dirs.push_back(UP);
    } 
    if(!current_cell.walls[RIGHT] && !current_cell.IsCellVisited(RIGHT)){ //Check RIGHT
        possible_dirs.push_back(RIGHT);
    }
    if(!current_cell.walls[DOWN] && !current_cell.IsCellVisited(DOWN)){ //Check DOWN
        possible_dirs.push_back(DOWN);
    }
    if(!current_cell.walls[LEFT] && !current_cell.IsCellVisited(LEFT)){ //Check LEFT
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
