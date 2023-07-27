#include <maze_controller.h>
#include <algorithms.h>
#include <thread>

void UserEventController(MazeController* maze_controller, Algorithms* algorithm_controller)
{
    SDL_Event e;
    while(true)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                SDL_Quit();
                delete maze_controller;
                // delete algorithm_controller;
                // abort();
            }
        }
    }
}

int main(){


    MazeController* maze_controller = new MazeController();
    Cell** maze = maze_controller->GetMaze();
    Algorithms* algorithm_controller = new Algorithms(maze, *maze_controller);

    // std::thread event_controller_thread(UserEventController, maze_controller, algorithm_controller);

    algorithm_controller->GenerateRandomMaze(&maze[0][0]);
    algorithm_controller->ClearVisitedCells();

    maze_controller->DrawGrid();
    SDL_RenderPresent(maze_controller->GetRenderer());

    // algorithm_controller->SetStartTime();

    // algorithm_controller->BruteForce(&maze[0][0]);
    algorithm_controller->AStar(&maze[0][0]);
    // maze_controller->DrawGrid();

    // maze_controller->ShowWindow();

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
