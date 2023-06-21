#include <maze_controller.h>
#include <algorithms.h>
#include <thread>

int main(){

    MazeController* maze_controller = new MazeController();


    Cell** maze = maze_controller->GetMaze();
    std::cout << "maze_controller main: " << maze_controller << std::endl;
    Algorithms *algorithm_controller = new Algorithms(maze, *maze_controller);
    algorithm_controller->GenerateRandomMaze(&maze[0][0]);
    algorithm_controller->ClearVisitedCells();
    std::cout << "alg::maze dir: " << algorithm_controller->GetMaze() << std::endl;
    maze_controller->DrawGrid(algorithm_controller->GetMaze());
    SDL_RenderPresent(maze_controller->GetRenderer());

    std::this_thread::sleep_for(std::chrono::seconds(2));

    algorithm_controller->SetStartTime();

    algorithm_controller->BruteForce(&maze[0][0]);
    std::cout << "Solved Brute Force" << std::endl;
    maze_controller->DrawGrid(maze_controller->GetMaze());
    // algorithm_controller.SolveA_Star(maze_controller->GetMaze()[20][20]);

    maze_controller->ShowWindow();

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

    
    return 0;
}
