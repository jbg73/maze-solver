#include <ui_controller.h>
#include <maze_generator.h>



int main(){

    UIController* ui_controller = new UIController();

    MazeController* maze_controller = new MazeController();

    bool walls[4] = {true,true,true,true};
    Cell initial_cell(0, 0, walls);
    maze_controller->GenerateRandomMaze(initial_cell);

    std::cout << "Maze generated" << std::endl;

    ui_controller->DrawGrid(maze_controller->GetMaze());

    ui_controller->PaintCell(initial_cell);
    
    ui_controller->ShowWindow();

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

    delete ui_controller;
    
    return 0;
}