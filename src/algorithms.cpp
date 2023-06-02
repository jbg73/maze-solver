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
    SDL_Delay(1);
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(actual_time - start_time).count() << std::endl;
    if(std::chrono::duration_cast<std::chrono::milliseconds>(actual_time - start_time).count() > 5000) return;
    else{
        int v1 = rand() % 4;
        Cell next_cell = current_cell.GetNextCell(static_cast<DIRECTION>(v1));
        SolveA_Star(next_cell);
        
    }

}