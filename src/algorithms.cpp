#include <algorithms.h>
#include <globals.h>

Algorithms::Algorithms(Cell **maze_ref, MazeController &maze_controller_ref) : maze_controller{maze_controller_ref}
{
    maze = maze_ref;
    std::cout << "maze controller alg: " << &maze_controller << std::endl;
}

Algorithms::~Algorithms()
{
    // delete maze;
    // SDL_DestroyRenderer(renderer);
}

bool Algorithms::IsVisited(Cell *cell) const
{
    for (int i = 0; i < current_path.size(); i++)
    {
        if (current_path[i]->x == cell->x && current_path[i]->y == cell->y)
            return true;
    }
    return false;
}

void Algorithms::UpdateCellWalls(Cell *c, DIRECTION dir)
{
    switch (dir)
    {
    case UP:
        c->walls[UP] = false;
        maze[c->x][c->y - 1].walls[DOWN] = false;
        break;

    case RIGHT:
        c->walls[RIGHT] = false;
        maze[c->x + 1][c->y].walls[LEFT] = false;
        break;

    case DOWN:
        c->walls[DOWN] = false;
        maze[c->x][c->y + 1].walls[UP] = false;
        break;

    case LEFT:
        c->walls[LEFT] = false;
        maze[c->x - 1][c->y].walls[RIGHT] = false;
        break;

    case NONE:
        break;

    default:
        break;
    }
}

Cell *Algorithms::GetNextCell(Cell *current_cell, DIRECTION dir)
{
    switch (dir)
    {
    case UP:
        return &maze[current_cell->x][current_cell->y - 1];
        break;

    case RIGHT:
        return &maze[current_cell->x + 1][current_cell->y];
        break;

    case DOWN:
        return &maze[current_cell->x][current_cell->y + 1];
        break;

    case LEFT:
        return &maze[current_cell->x - 1][current_cell->y];
        break;

    case NONE:
        break;

    default:
        return nullptr;
    }
    return nullptr;
}

void Algorithms::GenerateRandomMaze(Cell *current_cell)
{
    current_path.push_back(current_cell);
    // current_cell->visited_neighbours.push_back(maze[current_cell->x][current_cell->y]);
    while (current_cell->HasNonVisitedNeighbours())
    {
        DIRECTION next_dir = SelectRandomPossibleDirectionGenerating(current_cell);
        if (next_dir == NONE)
            return;
        UpdateCellWalls(current_cell, next_dir);
        // Cell next_cell = current_cell.GetNextCell(next_dir);
        // DisplayVisitedCells();
        Cell *next_cell = GetNextCell(current_cell, next_dir);
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

void Algorithms::BruteForce(Cell *current_cell)
{
    current_path.push_back(current_cell);
    maze_controller.ShowPath(current_path);
    SDL_Delay(150);
    if (current_cell->x == GRID_WIDTH - 1 && current_cell->y == GRID_HEIGHT - 1)
    {
        std::cout << "Found last cell" << std::endl;
        maze_controller.PaintCell(current_cell, 255, 0, 0);
        SDL_RenderPresent(maze_controller.GetRenderer());
        SDL_Delay(5);
        solved = true;
        return;
    }

    else
    {
        while (current_cell->HasAvailableConnections() && !solved)
        {
            DIRECTION next_dir = SelectRandomPossibleDirection(current_cell);
            if (next_dir != NONE)
            {
                Cell *next_cell = GetNextCell(current_cell, next_dir);
                current_cell->visited_neighbours.push_back(next_dir);
                next_cell->UpdateNextCellVisitedNeighbours(next_dir);
                BruteForce(next_cell);
            }
            current_path.pop_back();
        }
    }
}

void Algorithms::AStar(Cell *current_cell)
{
    std::vector<Cell *> neighbour_cells;
    InitializeAStar();
    cells_to_test.push_back(current_cell);
    while (!cells_to_test.empty())
    {
        std::cout << "solving..." << std::endl;
        current_cell = *cells_to_test.begin();
        neighbour_cells = GetPossibleNeighbours(current_cell);
        for (auto neighbour : neighbour_cells)
        {
            if (current_cell->local_dist + 1 < neighbour->local_dist)
            {
                if ((neighbour->x * CELL_SIZE) != GRID_WIDTH - 1 && (neighbour->y * CELL_SIZE) != GRID_HEIGHT - 1)
                {
                    cells_to_test.push_back(neighbour);
                }
                neighbour->parent = current_cell;
                neighbour->local_dist = current_cell->local_dist + 1;
                neighbour->global_dist = neighbour->local_dist + ManhattanDistance(neighbour);
            }
        }
        cells_to_test.erase(cells_to_test.begin());
        // visited_cells.add(current_cell);
        cells_to_test.sort([](Cell *c1, Cell *c2)
                           { return c1->global_dist < c2->global_dist; });
    }
    
    std::cout << "-----------------------------------------------------------------" << std::endl;
    Cell* aux = &maze[GRID_WIDTH-1][GRID_HEIGHT-1];
    while(aux->x != 0 || aux->y != 0)
    {
        std::cout << aux->x << "-" << aux->y << std::endl;
        current_path.push_back(aux);
        maze_controller.PaintCell(aux, 255,0,0);
        aux = aux->parent;
    }
    maze_controller.PaintCell(aux, 255,0,0);
    // maze_controller.ShowPath(current_path);
    std::cout << "Found path of " << current_path.size() << " steps" << std::endl;
}

void Algorithms::InitializeAStar()
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            maze[i][j].local_dist = INT32_MAX;
            maze[i][j].global_dist = INT32_MAX;
        }
    }
    maze[0][0].global_dist = ManhattanDistance(&maze[0][0]);
    maze[0][0].local_dist = 0;
}

int Algorithms::ManhattanDistance(Cell *current_cell)
{
    return abs((current_cell->x * CELL_SIZE) - GRID_WIDTH) + abs((current_cell->y * CELL_SIZE) - GRID_HEIGHT);
}

std::vector<Cell *> Algorithms::GetPossibleNeighbours(Cell *current_cell)
{
    std::vector<Cell *> neighbours;
    // Check UP
    if (current_cell->y - 1 >= 0 && !current_cell->walls[UP])
    {
        neighbours.push_back(GetNextCell(current_cell, UP));
    }
    // Check RIGHT
    if (current_cell->x + 1 < GRID_WIDTH && !current_cell->walls[RIGHT])
    {
        neighbours.push_back(GetNextCell(current_cell, RIGHT));
    }
    // Check DOWN
    if (current_cell->y + 1 < GRID_HEIGHT && !current_cell->walls[DOWN])
    {
        neighbours.push_back(GetNextCell(current_cell, DOWN));
    }
    // Check LEFT
    if (current_cell->x - 1 >= 0 && !current_cell->walls[LEFT])
    {
        neighbours.push_back(GetNextCell(current_cell, LEFT));
    }
    return neighbours;
}

DIRECTION Algorithms::SelectRandomPossibleDirection(Cell *current_cell)
{

    std::vector<DIRECTION> possible_dirs;

    if (current_cell->y - 1 >= 0 && !current_cell->walls[UP] && !IsVisited(&maze[current_cell->x][current_cell->y - 1]))
    { //Check UP
        possible_dirs.push_back(UP);
    }
    if (current_cell->x + 1 < GRID_WIDTH && !current_cell->walls[RIGHT] && !IsVisited(&maze[current_cell->x + 1][current_cell->y]))
    { //Check RIGHT
        possible_dirs.push_back(RIGHT);
    }
    if (current_cell->y + 1 < GRID_HEIGHT && !current_cell->walls[DOWN] && !IsVisited(&maze[current_cell->x][current_cell->y + 1]))
    { //Check DOWN
        possible_dirs.push_back(DOWN);
    }
    if (current_cell->x - 1 >= 0 && !current_cell->walls[LEFT] && !IsVisited(&maze[current_cell->x - 1][current_cell->y]))
    { //Check LEFT
        possible_dirs.push_back(LEFT);
    }

    if (possible_dirs.size() > 0)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, possible_dirs.size() - 1);
        return possible_dirs[dist(rng)];
    }

    return NONE;
}

DIRECTION Algorithms::SelectRandomPossibleDirectionGenerating(Cell *current_cell)
{

    std::vector<DIRECTION> possible_dirs;

    if (current_cell->y - 1 >= 0 && current_cell->walls[UP] && !IsVisited(&maze[current_cell->x][current_cell->y - 1]))
    { //Check UP
        possible_dirs.push_back(UP);
    }
    if (current_cell->x + 1 < GRID_WIDTH && current_cell->walls[RIGHT] && !IsVisited(&maze[current_cell->x + 1][current_cell->y]))
    { //Check RIGHT
        possible_dirs.push_back(RIGHT);
    }
    if (current_cell->y + 1 < GRID_HEIGHT && current_cell->walls[DOWN] && !IsVisited(&maze[current_cell->x][current_cell->y + 1]))
    { //Check DOWN
        possible_dirs.push_back(DOWN);
    }
    if (current_cell->x - 1 >= 0 && current_cell->walls[LEFT] && !IsVisited(&maze[current_cell->x - 1][current_cell->y]))
    { //Check LEFT
        possible_dirs.push_back(LEFT);
    }

    if (possible_dirs.size() > 0)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, possible_dirs.size() - 1);
        return possible_dirs[dist(rng)];
    }

    return NONE;
}
