#include <cell.h>
#include <random>

std::vector<Cell> Cell::visited_cells;

bool Cell::IsCellVisited() const{
    for(int i = 0; i < visited_cells.size(); i++){
        if(visited_cells[i].x == x && visited_cells[i].y == y) 
            return true;
    }
    return false;
}

bool Cell::IsCellVisited(int pos_x, int pos_y) const{
    for(int i = 0; i < visited_cells.size(); i++){
        if(visited_cells[i].x == pos_x && visited_cells[i].y == pos_y) 
            return true;
    }
    return false;
}

bool Cell::HasNonVisitedNeighbours() const{
    //Check UP
    if(y-1 >= 0 && !IsCellVisited(x, y-1)) return true;
    //Check RIGHT
    if(x+1 < GRID_WIDTH && !IsCellVisited(x+1, y)) return true;
    //Check Bottom
    if(y+1 < GRID_HEIGHT && !IsCellVisited(x, y+1)) return true;
    //Check left
    if(x-1 >= 0 && !IsCellVisited(x-1, y)) return true;

    return false;
}

DIRECTION Cell::SelectRandomPossibleDirection() const{
    std::vector<DIRECTION> non_visited_neighbours;
    //Check UP
    if(y-1 >= 0 && !IsCellVisited(x, y-1)) non_visited_neighbours.push_back(UP);
    //Check RIGHT
    if(x+1 < GRID_WIDTH && !IsCellVisited(x+1, y)) non_visited_neighbours.push_back(RIGHT);
    //Check Bottom
    if(y+1 < GRID_HEIGHT && !IsCellVisited(x, y+1)) non_visited_neighbours.push_back(DOWN);
    //Check left
    if(x-1 >= 0 && !IsCellVisited(x-1, y)) non_visited_neighbours.push_back(LEFT);

    if(non_visited_neighbours.size() > 0){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, non_visited_neighbours.size() - 1);
        return static_cast<DIRECTION>(non_visited_neighbours[dist(rng)]);
        // int selected_dir = dist(rng);
        // DIRECTION dir = static_cast<DIRECTION>(non_visited_neighbours[selected_dir]);
        // return static_cast<DIRECTION>(non_visited_neighbours[selected_dir]);
    }
    return NONE;
}

Cell Cell::GetNextCell(DIRECTION dir) const{
    Cell next_cell;

    switch(dir){
        case UP: //UP
            next_cell.x = x;
            next_cell.y = y-1;
            break;
        
        case RIGHT: //RIGHT
            next_cell.x = x+1;
            next_cell.y = y;
            break;
        
        case DOWN: //DOWN
            next_cell.x = x;
            next_cell.y = y+1;
            break;
        
        case LEFT: //LEFT
            next_cell.x = x-1;
            next_cell.y = y;
            break;
        
        default:
            break;
    }
    return next_cell;
}

std::vector<std::pair<int,int>> Cell::GetCellEdges() const{
    std::vector<std::pair<int,int>> cell_edges(4);

    cell_edges[0] = std::make_pair(x*CELL_SIZE, y*CELL_SIZE); // top left
    cell_edges[1] = std::make_pair((x+1)*CELL_SIZE, y*CELL_SIZE); // top right
    cell_edges[2] = std::make_pair((x+1)*CELL_SIZE, (y+1)*CELL_SIZE); // bottom right
    cell_edges[3] = std::make_pair(x*CELL_SIZE, (y+1)*CELL_SIZE); // bottom left

    return cell_edges;
}