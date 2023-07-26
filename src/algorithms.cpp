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

void Algorithms::UpdateCellWalls(Cell *c, globals::DIRECTION dir)
{
    switch (dir)
    {
    case globals::UP:
        c->walls[globals::UP] = false;
        maze[c->x][c->y - 1].walls[globals::DOWN] = false;
        break;

    case globals::RIGHT:
        c->walls[globals::RIGHT] = false;
        maze[c->x + 1][c->y].walls[globals::LEFT] = false;
        break;

    case globals::DOWN:
        c->walls[globals::DOWN] = false;
        maze[c->x][c->y + 1].walls[globals::UP] = false;
        break;

    case globals::LEFT:
        c->walls[globals::LEFT] = false;
        maze[c->x - 1][c->y].walls[globals::RIGHT] = false;
        break;

    case globals::NONE:
        break;

    default:
        break;
    }
}

Cell *Algorithms::GetNextCell(Cell *current_cell, globals::DIRECTION dir)
{
    switch (dir)
    {
    case globals::UP:
        return &maze[current_cell->x][current_cell->y - 1];
        break;

    case globals::RIGHT:
        return &maze[current_cell->x + 1][current_cell->y];
        break;

    case globals::DOWN:
        return &maze[current_cell->x][current_cell->y + 1];
        break;

    case globals::LEFT:
        return &maze[current_cell->x - 1][current_cell->y];
        break;

    case globals::NONE:
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
        globals::DIRECTION next_dir = SelectRandomPossibleDirectionGenerating(current_cell);
        if (next_dir == globals::NONE)
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
//         Cell next_cell = current_cell.GetNextCell(static_cast<globals::DIRECTION>(v1));
//         SolveA_Star(next_cell);

//     }

// }

void Algorithms::BruteForce(Cell *current_cell)
{
    current_path.push_back(current_cell);
    maze_controller.ShowPath(current_path);
    SDL_Delay(150);
    if (current_cell->x == globals::GRID_WIDTH - 1 && current_cell->y == globals::GRID_HEIGHT - 1)
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
            globals::DIRECTION next_dir = SelectRandomPossibleDirection(current_cell);
            if (next_dir != globals::NONE)
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
                if ((neighbour->x * globals::CELL_SIZE) != globals::GRID_WIDTH - 1 && (neighbour->y * globals::CELL_SIZE) != globals::GRID_HEIGHT - 1)
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
    Cell* aux = &maze[globals::GRID_WIDTH-1][globals::GRID_HEIGHT-1];
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
    for (int i = 0; i < globals::GRID_WIDTH; i++)
    {
        for (int j = 0; j < globals::GRID_HEIGHT; j++)
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
    return abs((current_cell->x * globals::CELL_SIZE) - globals::GRID_WIDTH) + abs((current_cell->y * globals::CELL_SIZE) - globals::GRID_HEIGHT);
}

std::vector<Cell *> Algorithms::GetPossibleNeighbours(Cell *current_cell)
{
    std::vector<Cell *> neighbours;
    // Check globals::UP
    if (current_cell->y - 1 >= 0 && !current_cell->walls[globals::UP])
    {
        neighbours.push_back(GetNextCell(current_cell, globals::UP));
    }
    // Check globals::RIGHT
    if (current_cell->x + 1 < globals::GRID_WIDTH && !current_cell->walls[globals::RIGHT])
    {
        neighbours.push_back(GetNextCell(current_cell, globals::RIGHT));
    }
    // Check globals::DOWN
    if (current_cell->y + 1 < globals::GRID_HEIGHT && !current_cell->walls[globals::DOWN])
    {
        neighbours.push_back(GetNextCell(current_cell, globals::DOWN));
    }
    // Check globals::LEFT
    if (current_cell->x - 1 >= 0 && !current_cell->walls[globals::LEFT])
    {
        neighbours.push_back(GetNextCell(current_cell, globals::LEFT));
    }
    return neighbours;
}

globals::DIRECTION Algorithms::SelectRandomPossibleDirection(Cell *current_cell)
{

    std::vector<globals::DIRECTION> possible_dirs;

    if (current_cell->y - 1 >= 0 && !current_cell->walls[globals::UP] && !IsVisited(&maze[current_cell->x][current_cell->y - 1]))
    { //Check globals::UP
        possible_dirs.push_back(globals::UP);
    }
    if (current_cell->x + 1 < globals::GRID_WIDTH && !current_cell->walls[globals::RIGHT] && !IsVisited(&maze[current_cell->x + 1][current_cell->y]))
    { //Check globals::RIGHT
        possible_dirs.push_back(globals::RIGHT);
    }
    if (current_cell->y + 1 < globals::GRID_HEIGHT && !current_cell->walls[globals::DOWN] && !IsVisited(&maze[current_cell->x][current_cell->y + 1]))
    { //Check globals::DOWN
        possible_dirs.push_back(globals::DOWN);
    }
    if (current_cell->x - 1 >= 0 && !current_cell->walls[globals::LEFT] && !IsVisited(&maze[current_cell->x - 1][current_cell->y]))
    { //Check globals::LEFT
        possible_dirs.push_back(globals::LEFT);
    }

    if (possible_dirs.size() > 0)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, possible_dirs.size() - 1);
        return possible_dirs[dist(rng)];
    }

    return globals::NONE;
}

globals::DIRECTION Algorithms::SelectRandomPossibleDirectionGenerating(Cell *current_cell)
{

    std::vector<globals::DIRECTION> possible_dirs;

    if (current_cell->y - 1 >= 0 && current_cell->walls[globals::UP] && !IsVisited(&maze[current_cell->x][current_cell->y - 1]))
    { //Check globals::UP
        possible_dirs.push_back(globals::UP);
    }
    if (current_cell->x + 1 < globals::GRID_WIDTH && current_cell->walls[globals::RIGHT] && !IsVisited(&maze[current_cell->x + 1][current_cell->y]))
    { //Check globals::RIGHT
        possible_dirs.push_back(globals::RIGHT);
    }
    if (current_cell->y + 1 < globals::GRID_HEIGHT && current_cell->walls[globals::DOWN] && !IsVisited(&maze[current_cell->x][current_cell->y + 1]))
    { //Check globals::DOWN
        possible_dirs.push_back(globals::DOWN);
    }
    if (current_cell->x - 1 >= 0 && current_cell->walls[globals::LEFT] && !IsVisited(&maze[current_cell->x - 1][current_cell->y]))
    { //Check globals::LEFT
        possible_dirs.push_back(globals::LEFT);
    }

    if (possible_dirs.size() > 0)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, possible_dirs.size() - 1);
        return possible_dirs[dist(rng)];
    }

    return globals::NONE;
}
