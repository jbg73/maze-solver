#include <ui_controller.h>
#include <maze_controller.h>
#include <algorithms.h>
#include <thread>

int main(){

    UIController* ui_controller = new UIController();

    MazeController* maze_controller = new MazeController();

    maze_controller->GenerateRandomMaze(maze_controller->GetMaze()[0][0]);

    std::cout << "Maze generated" << std::endl;
    maze_controller->GetMaze()[0][0].ClearVisitedCells();
    

    ui_controller->DrawGrid(maze_controller->GetMaze());
    SDL_RenderPresent(ui_controller->GetRenderer());
    // std::string a;
    // // getline (std::cin, a);
    // getline(std::cin);
    // std::cin.get();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Algorithms algorithm_controller(*maze_controller, *ui_controller); //TODO: Why do I need *

    algorithm_controller.SetStartTime();

    algorithm_controller.BruteForce(maze_controller->GetMaze()[0][0]);
    std::cout << "Solved Brute Force" << std::endl;
    ui_controller->DrawGrid(maze_controller->GetMaze());
    // algorithm_controller.SolveA_Star(maze_controller->GetMaze()[20][20]);

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
